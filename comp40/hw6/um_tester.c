#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitpack.h"
#include "inttypes.h"
#include "assert.h"
#include "fmt.h"
#include "seq.h"

#define NTESTS (sizeof(tests)/sizeof(tests[0]))

typedef uint32_t Um_instruction;
typedef unsigned Um_opcode;

/* used to store different instructions onto command sequence */
/* emit_out_string repeates necessary instructions for whole string */
 void emit(Seq_T stream, Um_instruction inst);
static void emit_out_string(Seq_T stream, const char *s, int aux_reg);

/* 14 instructions to emit onto command sequence */
 Um_instruction conditional_move(unsigned ra, unsigned rb, unsigned rc);
 Um_instruction segmented_load(unsigned ra, unsigned rb, unsigned rc);
 Um_instruction segmented_store(unsigned ra, unsigned rb, unsigned rc);
 Um_instruction addition(unsigned ra, unsigned rb, unsigned rc);
 Um_instruction multiplication(unsigned ra, unsigned rb, unsigned rc);
 Um_instruction division(unsigned ra, unsigned rb, unsigned rc);
 Um_instruction bitwise_NAND(unsigned ra, unsigned rb, unsigned rc);
 Um_instruction halt(void);
 Um_instruction map_segment(unsigned rb, unsigned rc);
 Um_instruction unmap_segment(unsigned rc);
 Um_instruction output(unsigned rc);
 Um_instruction input(unsigned rc);
 Um_instruction load_program(unsigned rb, unsigned rc);
 Um_instruction load_value(unsigned ra, unsigned val);

/* additional functions used to output and interact with sequence */
extern void Um_write_sequence(FILE *output, Seq_T stream);
 Um_instruction get_inst(Seq_T stream, int i);
 void put_inst(Seq_T stream, int i, Um_instruction inst);
static void add_label(Seq_T stream, int location_to_patch, int label_value);
static FILE *open_and_free_pathname(char *path);
static void write_or_remove_file(char *path, const char *contents);

enum instruction { CMOV = 0, SLOAD, SSTORE, ADD, MULT, DIV, NAND, HALT, MAP, 
                   UNMAP, OUTPUT, INPUT, LOADP, LOADV };

enum regs { r0 = 0, r1, r2, r3, r4, r5, r6, r7 };

/**********************************/
/* INSERT USER CREATED TESTS HERE */
/**********************************/

void emit_halt_test(Seq_T stream)
{
        emit(stream, halt());
        emit(stream, load_value(r1, 'B'));
        emit(stream, output(r1));
        emit(stream, load_value(r1, 'a'));
        emit(stream, output(r1));
        emit(stream, load_value(r1, 'd'));
        emit(stream, output(r1));
        emit(stream, load_value(r1, '!'));
        emit(stream, output(r1));
        emit(stream, load_value(r1, '\n'));
        emit(stream, output(r1));
}

void emit_goto_test(Seq_T stream)
{
        int patch_L = Seq_length(stream);
        emit(stream, load_value(r7, 0));    /* will be patched to 'r7 := L' */
        emit(stream, load_program(r0, r7)); /* should goto label L          */
        emit_out_string(stream, "GOTO failed.\n", r1);
        emit(stream, halt());

        /* define 'L' to be here */
        add_label(stream, patch_L, Seq_length(stream));        
        emit_out_string(stream, "GOTO passed.\n", r1);
        emit(stream, halt());
}

void emit_IO_test(Seq_T stream)
{
        emit(stream, input(r1));
        emit(stream, output(r1));
        emit(stream, halt());
}

void emit_load_program_test(Seq_T stream)
{
        emit(stream, load_value(r1, 3));
        emit(stream, load_program(r0, r1)); 
        emit(stream, halt());
        emit_out_string(stream, "Success!\n", r1);
        emit(stream, halt());
}

/* tests basic math computation with the math commands */
void emit_math_test(Seq_T stream)
{
        emit(stream, load_value(r1, 51));
        emit(stream, load_value(r2, 50));
        emit(stream, addition(r3, r1, r2));
        emit(stream, output(r3));

        emit(stream, load_value(r4, 1));
        emit(stream, load_value(r5, 50));
        emit(stream, multiplication(r6, r4, r5));
        emit(stream, output(r6));

        emit(stream, load_value(r2, 54));
        emit(stream, division(r1, r2, r4));
        emit(stream, division(r3, r2, r4));
        emit(stream, output(r1));
        emit(stream, output(r3));

        emit(stream, halt());
}

/* tests the ability to store and load values from segments */
void emit_seg_store_load_test(Seq_T stream)
{
        emit(stream, load_value(r2, 5));
        emit(stream, load_value(r3, 2));
        emit(stream, load_value(r4, 52));
        
        /* make new segment of length 5 */
        emit(stream, map_segment(r1, r2));
        
        /* store 52 into 3rd word of new segment */
        emit(stream, segmented_store(r1, r3, r4));

        /* get back 52 from 3rd word of new segment */
        emit(stream, segmented_load(r5, r1, r3));

        emit(stream, output(r5));
        emit(stream, halt());
}

/* tests ability to map and unmap a segment to see if it correctly initalizes */
void emit_map_unmap_test(Seq_T stream)
{
        /* load initial values */
        emit(stream, load_value(r2, 5));
        emit(stream, load_value(r3, 2));
        emit(stream, load_value(r4, 52));
        emit(stream, load_value(r6, 33));        

        /* make new segment of length 5 */
        /* store value and check it worked */
        emit(stream, map_segment(r1, r2));
        emit(stream, segmented_store(r1, r3, r4));
        emit(stream, segmented_load(r5, r1, r3)); 
        emit(stream, output(r5));

        /* unmap and re-map segment to same size */
        emit(stream, unmap_segment(r1));
        emit(stream, map_segment(r1, r2));

        /* check if value was reset back to 0 */
        emit(stream, segmented_load(r5, r1, r3)); 
        emit(stream, addition(r5, r5, r6));
        emit(stream, output(r5));
        
        emit(stream, halt());
}

/* tests ability to load program from another segment (not m[0]) */
void emit_load_other_seg_test(Seq_T stream)
{
        /* map segment of length 100 */
        emit(stream, load_value(r1, 100));
        emit(stream, map_segment(r2, r1));

        /* does computation to make halt() instruction */
        emit(stream, load_value(r7, 128));
        emit(stream, load_value(r3, 14680064));
        emit(stream, multiplication(r3, r3, r7));

        /* stores instruction on new segment */
        emit(stream, load_value(r5, 0));
        emit(stream, segmented_store(r2, r5, r3));

        /* ~should~ jump to new segment for halt() */
        emit(stream, load_program(r2, r5));
        emit_out_string(stream, "Bad\n", r6);
        emit(stream, halt());
}

void emit_for_loop_test(Seq_T stream)
{
        emit(stream, load_value(r1, 48));
        emit(stream, load_value(r2, 1));
        emit(stream, load_value(r3, 65));

        emit(stream, load_value(r5, 5));
        emit(stream, load_value(r6, 10));

        emit(stream, output(r1));
        emit(stream, addition(r1, r1, r2));

        emit(stream, division(r4, r1, r3));
        emit(stream, conditional_move(r5, r6, r4));
        
        emit(stream, load_program(r7, r5));
        emit_out_string(stream, "\nloop finished\n", r1);
        emit(stream, halt());
}

void emit_all_instructions_test(Seq_T stream)
{
        emit(stream, load_value(r1, 3));
        emit(stream, load_program(r7, r1));
        emit(stream, halt());

        emit(stream, input(r1));
        emit(stream, output(r1));
        emit(stream, load_value(r1, 33));
        emit(stream, output(r1));
        emit(stream, conditional_move(r1, r2, r3));

        emit(stream, load_value(r1, 5));
        emit(stream, load_value(r3, 982039));
        emit(stream, load_value(r5, 8183));
        emit(stream, map_segment(r2, r1));
        emit(stream, segmented_store(r2, r7, r3));
        emit(stream, segmented_load(r4, r2, r7));
        emit(stream, division(r4, r4, r5));
        emit(stream, output(r4));
        
        emit(stream, load_value(r1, 1));
        emit(stream, addition(r4, r4, r1));
        emit(stream, output(r4));

        emit(stream, bitwise_NAND(r5, r5, r3));

        emit(stream, unmap_segment(r2));

        emit(stream, halt());
}

/* tests the user can't make the program counter go outside boudns of m[0] */
void emit_failure_case_1_test(Seq_T stream)
{
        emit(stream, load_value(r1, 0));
        emit(stream, load_value(r2, 100));
        emit(stream, load_program(r1, r2));
        emit(stream, halt());
}

/* tests that the user can't load from an unmapped segment */
void emit_failure_case_3_test(Seq_T stream)
{
        emit(stream, load_value(r1, 2));
        emit(stream, load_value(r2, 3));
        emit(stream, segmented_load(r3, r1, r2));
        emit(stream, halt());
}

/* tests that the user cannot access a segment outside its bounds */
void emit_failure_case_4_test(Seq_T stream)
{
        emit(stream, load_value(r1, 5));
        emit(stream, load_value(r3, 10));
        emit(stream, map_segment(r2, r1));
        emit(stream, segmented_load(r7, r2, r3));

        emit(stream, halt());
}

/* tests that the user cannot unmap an already unmapped segment */
/* also tests that the user cannot unmap m[0] */
void emit_failure_case_5_test(Seq_T stream)
{
        emit(stream, load_value(r1, 2));
        emit(stream, load_value(r2, 0));
        emit(stream, unmap_segment(r1));
        emit(stream, unmap_segment(r2));

        emit(stream, halt());
}

/* tests the user can't divide by 0 */
void emit_failure_case_6_test(Seq_T stream)
{
        emit(stream, load_value(r1, 2));
        emit(stream, division(r2, r1, r5));
        emit(stream, halt());
}

/* tests the user can't load program for an unmapped segment */
void emit_failure_case_7_test(Seq_T stream)
{
        emit(stream, load_value(r1, 2));
        emit(stream, load_program(r1, r2));
        emit(stream, halt());
}

/* tests that the user can't output a character value outside ASCII bounds */
/* doesn't fail assertion, just doesn't print anything */
void emit_failure_case_8_test(Seq_T stream)
{
        emit(stream, load_value(r1, 10000));
        emit(stream, output(r1));
        emit(stream, halt());
}

/******************************/
/* END OF USER CREATED TESTS  */
/*                            */
/* Update tests[] to include  */
/* new test(s)                */
/******************************/

static struct test_info {
        const char *name;
        const char *test_input;            /* NULL means no input needed */
        const char *expected_output;       /* "" means no output */
        void (*emit_test) (Seq_T stream);
} tests[] = {
        {"halt", NULL, "", emit_halt_test},
        {"goto", NULL, "GOTO passed.\n", emit_goto_test},
        {"IO", "5", "5", emit_IO_test},
        {"load_program", NULL, "Success!\n", emit_load_program_test},
        {"math", NULL, "e266", emit_math_test},
        {"seg_store_load", NULL, "4", emit_seg_store_load_test},
        {"map_unmap", NULL, "4!", emit_map_unmap_test},
        {"load_other_seg", NULL, "", emit_load_other_seg_test},
        {"for_loop", NULL, "0123456789:;<=>?@\nloop finished\n", 
                                                  emit_for_loop_test},
        {"all_instructions", "6", "6!xy", emit_all_instructions_test},
        {"failure_case_1", NULL, "", emit_failure_case_1_test},
        {"failure_case_3", NULL, "", emit_failure_case_3_test},
        {"failure_case_4", NULL, "", emit_failure_case_4_test},
        {"failure_case_5", NULL, "", emit_failure_case_5_test},
        {"failure_case_6", NULL, "", emit_failure_case_6_test},
        {"failure_case_7", NULL, "", emit_failure_case_7_test},
        {"failure_case_8", NULL, "", emit_failure_case_8_test},
};

static void write_test_files(struct test_info *test);

int main(int argc, char *argv[])
{
        bool failed = false;
        if (argc == 1)
                for (unsigned i = 0; i < NTESTS; i++) {
                        printf("***** Writing test '%s'.\n", tests[i].name);
                        write_test_files(&tests[i]);
        } else
                for (int j = 1; j < argc; j++) {
                        bool tested = false;
                        for (unsigned i = 0; i < NTESTS; i++)
                                if (!strcmp(tests[i].name, argv[j])) {
                                        tested = true;
                                        write_test_files(&tests[i]);
                                }
                        if (!tested) {
                                failed = true;
                                fprintf(stderr,
                                        "***** No test named %s *****\n",
                                        argv[j]);
                        }
                }
        return failed;   /* failed nonzero == exit nonzero == failure */
}

static void write_test_files(struct test_info *test)
{
        FILE *binary = open_and_free_pathname(Fmt_string("%s.um", test->name));
        Seq_T asm = Seq_new(0);
        test->emit_test(asm);
        Um_write_sequence(binary, asm);
        Seq_free(&asm);
        fclose(binary);

        write_or_remove_file(Fmt_string("%s.0", test->name), test->test_input);
        write_or_remove_file(Fmt_string("%s.1", test->name),
                             test->expected_output);
}

 void emit(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t) inst);
}

static void add_label(Seq_T stream, int location_to_patch, int label_value)
{
        Um_instruction inst = get_inst(stream, location_to_patch);
        unsigned k = Bitpack_getu(inst, 25, 0);
        inst = Bitpack_newu(inst, 25, 0, label_value + k);
        put_inst(stream, location_to_patch, inst);
}

static void emit_out_string(Seq_T stream, const char *s, int aux_reg)
{
        int i = 0;
        while (s[i] != '\0') {
                emit(stream, load_value(aux_reg, s[i]));
                emit(stream, output(aux_reg));
                i++;
        }
}

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
        unsigned word = Bitpack_newu(0, 4, 28, op);
        word = Bitpack_newu(word, 3, 6, ra);
        word = Bitpack_newu(word, 3, 3, rb);
        return Bitpack_newu(word, 3, 0, rc);
}

Um_instruction loadval(unsigned ra, unsigned val) 
{
        unsigned word = Bitpack_newu(0, 4, 28, 13);
        word = Bitpack_newu(word, 3, 25, ra);
        word = Bitpack_newu(word, 25, 0, val);
        return word; 
}

Um_instruction conditional_move(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(CMOV, ra, rb, rc);
}

 Um_instruction segmented_load(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(SLOAD, ra, rb, rc);
}

 Um_instruction segmented_store(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(SSTORE, ra, rb, rc);
}

 Um_instruction addition(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(ADD, ra, rb, rc);
}

 Um_instruction multiplication(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(MULT, ra, rb, rc);
}

 Um_instruction division(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(DIV, ra, rb, rc);
}

 Um_instruction bitwise_NAND(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(NAND, ra, rb, rc);
}

 Um_instruction halt(void)
{
        return three_register(HALT, 0, 0, 0);
}

 Um_instruction map_segment(unsigned rb, unsigned rc)
{
        return three_register(MAP, 0, rb, rc);
}

 Um_instruction unmap_segment(unsigned rc)
{
        return three_register(UNMAP, 0, 0, rc);
}

 Um_instruction output(unsigned rc)
{
        return three_register(OUTPUT, 0, 0, rc);
}

 Um_instruction input(unsigned rc)
{
        return three_register(INPUT, 0, 0, rc);
}

 Um_instruction load_program(unsigned rb, unsigned rc)
{
        return three_register(LOADP, 0, rb, rc);
}

 Um_instruction load_value(unsigned ra, unsigned val)
{
        return loadval(ra, val);
}

extern void Um_write_sequence(FILE *output, Seq_T asm)
{
        int length = Seq_length(asm);
        for (int i = 0; i < length; i++) {
                uint32_t instruction =  
                    (Um_instruction)(uintptr_t)Seq_get(asm, i);
                putc(Bitpack_getu(instruction, 8, 24), output);
                putc(Bitpack_getu(instruction, 8, 16), output);
                putc(Bitpack_getu(instruction, 8, 8), output);
                putc(Bitpack_getu(instruction, 8, 0), output);
        }
}

 Um_instruction get_inst(Seq_T stream, int i)
{
        assert(sizeof(Um_instruction) <= sizeof(uintptr_t));
        return (Um_instruction) (uintptr_t) (Seq_get(stream, i));
}

 void put_inst(Seq_T stream, int i, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_put(stream, i, (void *)(uintptr_t) inst);
}

/*
 * if contents is NULL or empty, remove the given 'path', 
 * otherwise write 'contents' into 'path'.  Either way, free 'path'.
 */
static void write_or_remove_file(char *path, const char *contents)
{
        if (contents == NULL || *contents == '\0') {
                remove(path);
        } else {
                FILE *input = fopen(path, "wb");
                assert(input);
                fputs(contents, input);
                fclose(input);
        }
        free(path);
}

/*
 * open file 'path' for writing, then free the pathname;
 * if anything fails, checked runtime error
 */
static FILE *open_and_free_pathname(char *path)
{
        FILE *fp = fopen(path, "wb");
        assert(fp != NULL);

        free(path);
        return fp;
}
