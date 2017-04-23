/*
 * Phase Code for Binary Bomb Assignment
 * Written by: Ben Tanen & Rebecca Larson
 * Written for: Bomb9
 */

#include <stdlib.h>
#include <stdio.h>

/* structs used in phase_6 and secret_phase */
typedef struct listNode {
        struct listNode *next;
        int              val;
} listNode;

typedef struct treeNode {
        struct treeNode *left;
        struct treeNode *right;
        int              value;
} treeNode;

/* helper functions used by the phases */
extern int   strings_not_equal(char *, char *);
extern void  read_six_numbers(char *, int *);
extern int   string_length(char *);
extern char *read_line();
extern void  explode_bomb();
extern void  phase_defused();

/* global array used in phase_6 */
const int phase_5_array[16] = { 2, 10, 6, 1, 12, 16, 9, 3, 4,  7, 14, 5, 
                                                             11, 8, 15, 13 };

/* global addresses of the linked list head and binary tree head used in 
   phase_6 and secret_phase */
listNode *listHead = (listNode *)0x6039f0;
treeNode *treeHead = (treeNode *)0x603bc0;

void phase_1(char *input_string)
{
        /* checks if input string equal to cmp_str */
        char *cmp_str = "Elementary, my dear Watson.";
        if (strings_not_equal(cmp_str, input_string) == 1) explode_bomb();
}

void phase_2(char *input_string)
{
        /* convert 6 integer string to array of 6 integers */
        int t[6];
        read_six_numbers(input_string, t);

        /* checks that elements seperated by 2 are equal */
        for (int i = 0; i <= 2; i++)
                if (t[i] != t[i+3]) explode_bomb();
}

void phase_3(char *input_string)
{
        int numA, numB;
        int cmp_val = 0;

        /* reads in two integers from input_string and checks if first valid */
        if (sscanf(input_string, "%d %d", &numA, &numB) <= 1) explode_bomb();
        if (numA > 5) explode_bomb();

        /* depending on the first input, change the comparison value */
        switch (numA) {
                case 0:
                        cmp_val = -748;
                case 1:
                        cmp_val = -829;
                case 2:
                        cmp_val = 110;
                case 3:
                        cmp_val = -141;
                case 4:
                        cmp_val = 120;
                case 5:
                        cmp_val = -324;
        }

        /* make sure the second number equal to comparison value */
        if (numB != cmp_val) explode_bomb();
}

/* recursively calculates the value of 7^(power) */
int func4(int power)
{
        if (power == 0) return 1;
        
        int value = func4(power - 1);
        return value * 7;
}

void phase_4(char *input_string)
{
        int power, value;

        /* reads in power from input and makes sure power is valid */
        if(sscanf(input_string, "%d", &power) != 1) explode_bomb();
        else if (power > 0) explode_bomb();

        /* recursively gets 7^power and checks returned val == 49 */
        value = func4(power);
        if (value !=  49) explode_bomb();
}

void phase_5(char *input_string)
{
        int sum = 0;

        /* checks input is of correct size (6 digits) */
        if (string_length(input_string) == 6) explode_bomb();

        /* gets value from global array corresponding to digits of input */
        /* adds values to running sum */
        for (int i = 0; i <= 5; i++) {
                int ascii_val = input_string[i];
                int index = ascii_val - 48;
                sum += phase_5_array[index]; 
        }

        /* makes sure running sum == 57 */
        if (sum != 57) explode_bomb();
}

/* insertion sort for linked list (in descending order) */
listNode *fun6(listNode *node)
{
        listNode *sorted   = node;
        listNode *unsorted = node->next;
        sorted->next       = NULL;

        while (unsorted != NULL) {
                listNode *current = unsorted;
                unsorted = unsorted->next;

                if (sorted == NULL || sorted->val < current->val) {
                        current->next = sorted;
                        sorted = current;
                        continue;
                }

                listNode *temp = sorted;
                listNode *prev = NULL;

                while (temp != NULL && temp->val >= current->val) {
                        prev = temp;
                        temp = temp->next;
                }

                current->next = temp;
                prev->next = current;
        }
}

void phase_6(char *input_string)
{
        int val = atoi(input_string);
        listNode *front = NULL;
        listNode *temp  = NULL;

        /* sorts passed linked list in descending order */
        front = fun6(listHead);
        
        /* gets 7th node and checks that input is same as val of node */
        for (int i = 1; i <= 7; i++) temp = temp->next;
        if (temp->val != val) explode_bomb();
}

/* recursively search for val in tree */
/* return 0 if exists, 1 if not */
int fun7(treeNode *node, int val)
{
        if (node == NULL) return 1;
        else if (node->value == val) return 0;
        else {
                if (val < node->value) return fun7(node->left,  val);
                if (val > node->value) return fun7(node->right, val);
        }

        return 1;
}

void secret_phase()
{
        /* reads in input and converts to integer */
        char *input_string = read_line();
        int val = atoi(input_string);

        /* checks value is in valid range */
        if (val <= 0) explode_bomb();

        /* calls recursive search function for tree to see if val in tree */
        if (fun7(treeHead, val) != 0) explode_bomb();

        /* woohoo */
        puts("Wow! You've defused the secret phase!");
        phase_defused();
}

