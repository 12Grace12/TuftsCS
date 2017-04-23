#include <iostream>
#include <cstdlib>
#include "ddrlib.h"
using namespace std;

// ddr.cpp: digital digit recognizer
//
//  purpose: read in plates of bitmaps and find the digits in those images
//     uses: a file of digit bitmaps
//    input: a sequence of images from cin
//   output: for each image, a list of the digits and their locations
//   format: 2 @ 2,1 3 @ 2,12 6 @ 3,20 ... -1
//  details: each digit is listed as the digit, a space, an @ sign,
//           a space, then the row, col with a comma (and no space)
//           between them.
//           The end of the list has a -1 sentinel value
//   errors: any character it cannot recognize is reported as
//           ? @ row,col   where row,col are the actual coordinates of
//           the upper left pixel in the character
//
//  Code by: Ben Tanen
//     Date: 02/26/2014
//

const int SENTINEL = -5;
const int results_size = 1000;

void analyze(char image[IMG_HGT][IMG_WID], 
             char digits[DIG_NUM][DIG_HGT][DIG_WID]);

// (See below for more detail on these functions)
void print_plate(char plate[IMG_HGT][IMG_WID]);
void analyze_cell(char plate[IMG_HGT][IMG_WID], 
                  int row, int col, 
                  int results[results_size][3], 
                  int no_test[results_size][2],
                  char digits[DIG_NUM][DIG_HGT][DIG_WID]);
void print_result(int results[results_size][3]);
void store_result(int num, int row, int col, int results[results_size][3]);
void make_no_test(int num, int row, int col, int no_test[results_size][2], 
                  char digits[DIG_NUM][DIG_HGT][DIG_WID], 
                  char plate[IMG_HGT][IMG_WID]);
bool should_test(int row, int col, int no_test[results_size][2]);
int determine_digit(int row, int col, 
                    char plate[IMG_HGT][IMG_WID], 
                    char digits[DIG_NUM][DIG_HGT][DIG_WID]);
bool compare_digits(int row, int col, 
                    char plate[IMG_HGT][IMG_WID], 
                    char digits[DIG_NUM][DIG_HGT][DIG_WID], int i);

int main(int ac, char *av[])
{
    char    digits[DIG_NUM][DIG_HGT][DIG_WID];
    char    image[IMG_HGT][IMG_WID];

    if ( ac == 1 ) {
        cerr << "usage: " << av[0] << " digit_bitmap_file\n";
        exit(1);
    }
    if ( read_patts( string(av[1]), digits, DIG_NUM ) != DIG_NUM ) {
        cerr << av[0] << ": error - too few digit bitmaps\n";
        exit(1);
    }
    open_image("");
    while ( next_image(image) ) {
        analyze(image, digits);
    }

    return 0;
}

// "Analyze" Function
// purpose: this function is the "brains" of the program. It feeds
//          to other functions that analyze the plate and determine/output
//          the numbers (and their location) on the plate
// arguments: takes in the plate[] array (char) and the digs[] array (char)
// returns: nothing
// effects: feeds to other functions that output the location of the
//          plate's numbers
// note: this is the overall parent function. Feeds to all below functions
//       (either directly or indirectly)
//
void analyze(char plate[IMG_HGT][IMG_WID],
             char digs[DIG_NUM][DIG_HGT][DIG_WID])
{
    int results[results_size][3];
    int no_test[results_size][2];
    results[0][0] = SENTINEL;
    no_test[0][0] = SENTINEL;
    
    char target = '#';    
    int  row = 0;
    int  col = 0;

    while (col<IMG_WID){
        row = 0;
        while (row<IMG_HGT){
            if (plate[row][col] == target && should_test(row,col,no_test)){
                analyze_cell(plate,row,col,results,no_test,digs); 
            } else {
                row++;  
            }
        }
        col++;
    }
    
    // print_plate(plate);  // << Used for testing purposes 
    print_result(results);

}

// "Print Plate" Function
// purpose: this function prints out each character in the plate[] array
//          in turn, which ultimatly prints the plate as a whole
// arguments: takes in the plate[] array (char)
// returns: nothing
// effects: prints out the given plate
// note: this is primarily used for testing purposes and is commented out
//       before the program was submitted
//
void print_plate(char plate[IMG_HGT][IMG_WID])
{
    for (int m=0;m<IMG_HGT;m++){
       for (int n=0;n<IMG_WID;n++){
           cout << plate[m][n];
        }
        cout << endl;
    }
}

// "Analyze Cell" Function
// purpose: once a "#" is found and it is determined that the cell is
//          not in the no_test[] array, this function uses the number-
//          analysis and point-analysis functions to decide a given
//          character is
// arguments: takes in the plate[] array (char), the location of the "#"
//            (col, row (int)), the results[] array (int), the no_test[] 
//            array (int), and the digs[] array (char)
// returns: nothing
// effects: nothing (see note)
// note: this function itself does nothing, but it does lead to other
//       functions (store_results, make_no_test) that modify the
//       results[] and no_test[] array
//
void analyze_cell(char plate[IMG_HGT][IMG_WID], 
                  int row, int col, 
                  int results[results_size][3], 
                  int no_test[results_size][2],
                  char digs[DIG_NUM][DIG_HGT][DIG_WID])
{
    
    int num;

    num = determine_digit(row,col,plate,digs);

    store_result(num,row,col,results);
    make_no_test(num,row,col,no_test,digs,plate);
} 

// "Print Result" Function
// purpose: this function takes in the results[] array and prints out
//          the number and its location in the designated format
// arguments: takes in the results[] array (int)
// returns: nothing (prints results)
// effects: this prints out the results from the results[] array
// note: if the number is unknown it returns a -1
//
void print_result(int results[results_size][3])
{
    int i=0;
    while (results[i][0] != SENTINEL){

        if (results[i][0] == -1){
            cout << "?";
        } else if (results[i][0] >= 0 && results[i][0] <= 9){
            cout << results[i][0];
        }

        cout << " @ " << results[i][1] << "," 
             << results[i][2] << " ";
        i++;
    }
    cout << -1 << endl;
}

// "Store Result" Function
// purpose: this function takes in the determined identity of a number and
//          its location and adds these to the results array that is used
//          at the end
// arguments: takes in the known identity of the number (int), the location
//            (int for col/row), and the results[] array
// returns: nothing (modifies result[])
// effects: this adds the number and the location of the number to the 
//          result[] array
// notes: none
//
void store_result(int num, int row, 
                  int col, int results[results_size][3])
{
    int i=0;
    while (results[i][0] != SENTINEL){
        i++;
    }
    results[i][0] = num;
    results[i][1] = row;
    results[i][2] = col;
    results[i+1][0] = SENTINEL;
}

// "Make No Test" Function
// purpose: this function takes in the below arguments and adds points to
//          the no_test array that is used to determine if the analyze
//          function should analyze a found point
// arguments: the known identify of the found number (int), the location
//            of the top left corner (int col/row), the no_test[] array (int)
//            and the digs[] array
// returns: nothing (modifies no_test[])
// effects: this adds certain point/locations to the no_test[] array
//          after it is determined these are part of the known number
// notes: none
//
void make_no_test(int num, int row, int col, int no_test[results_size][2], 
                  char digits[DIG_NUM][DIG_HGT][DIG_WID], 
                  char plate[IMG_HGT][IMG_WID])
{
    int i=0;
    char target = '#';
    while (no_test[i][0] != SENTINEL){
        i++;
    }

    for (int m=0; m < DIG_HGT; m++){
        for (int n=0; n < DIG_WID; n++){
            if (num >= 0 && num <= 9){
                if (digits[num][m][n] == target){
                    no_test[i][0] = m + row;
                    no_test[i][1] = n + col;
                }
            } else if (num == -1){
                if (plate[m+row][n+col] == target){
                    no_test[i][0] = m + row;
                    no_test[i][1] = n + col;
                }
            }
            i++;
        }
    }
    no_test[i][0] = SENTINEL;
}

// "Should Test" Test
// purpose: this function is given a particular point and then
//          searches through the no_test[] array to determine
//          if it should be tested
// arguments: integers for row and col (describing the point)
//            and the no_test[] array
// returns: true or false
// effects: no modifications
// notes: none
//
bool should_test(int row, int col, int no_test[results_size][2])
{
    int i=0;
    while (no_test[i][0] != SENTINEL){
        if (no_test[i][0] == row && no_test[i][1] == col){
            return false;
        }
        i++;
    }
    return true;
}

// "Determine Digit" Function
// purpose: this function goes through a for loop that determines what number
//          (or not digit) is located at a particular location
// arguments: integers for row and col (describing the point)
//            and the plate[] and digits array[].
// returns: an integer (the identity of the character)
// effects: no modifications
// notes: none
//
int determine_digit(int row, int col, 
                    char plate[IMG_HGT][IMG_WID], 
                    char digits[DIG_NUM][DIG_HGT][DIG_WID])
{
    for (int i=0;i<10;i++){
        if (compare_digits(row,col,plate,digits,i)) {
            return i;
        }
    }
    return -1;
}

// Compare Digits Function
// purpose: this function compares a particular digit (from the digits
//          array) with the character found on the plate and returns
//          whether the two are the same (based on bitmaps)
// arguments: integers for row and col (describing the point),
//            the plate[] and digits array[], and an integer
//            to test the plate character with
// returns: true/false (boolean)
// effects: no modifications
// notes: none
//
bool compare_digits(int row, int col, 
                    char plate[IMG_HGT][IMG_WID], 
                    char digits[DIG_NUM][DIG_HGT][DIG_WID], int i)
{
    for (int test_row=0;test_row<DIG_HGT;test_row++){
        for (int test_col=0;test_col<DIG_WID;test_col++){
            if (digits[i][test_row][test_col] != 
                plate[row+test_row][col+test_col]){
                return false;
            }
        }
    }
    return true;
}
