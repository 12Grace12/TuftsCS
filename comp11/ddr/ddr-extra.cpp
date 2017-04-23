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

// Testing Functions | These functions are used for testing purposes
void print_plate(char plate[IMG_HGT][IMG_WID]);
void analyze_cell(char plate[IMG_HGT][IMG_WID], 
                  int row, int col, 
                  int results[results_size][3], 
                  int no_test[results_size][2],
                  char digits[DIG_NUM][DIG_HGT][DIG_WID]);
void print_result(int results[results_size][3]);
void store_result(int num, int row, int col, int results[results_size][3]);
void make_no_test(int num, int row, int col, int no_test[results_size][2], 
                  char digits[DIG_NUM][DIG_HGT][DIG_WID]);
bool should_test(int row, int col, int no_test[results_size][2]);

// Function Type: Number Analysis
// Using the Pt-Analysis, these functions determine the particular number
bool is_1(char image[][IMG_WID], int col, int row);
bool is_2(char image[][IMG_WID], int col, int row);
bool is_3(char image[][IMG_WID], int col, int row);
bool is_4(char image[][IMG_WID], int col, int row);
bool is_5(char image[][IMG_WID], int col, int row);
bool is_6(char image[][IMG_WID], int col, int row);
bool is_7(char image[][IMG_WID], int col, int row);
bool is_8(char image[][IMG_WID], int col, int row);
bool is_9(char image[][IMG_WID], int col, int row);
bool is_0(char image[][IMG_WID], int col, int row);

// Function Type: Point Analysis
// Checks if there is a "#" at location (x,y)
bool pt_tm(char image[][IMG_WID], int col, int row);
bool pt_mtl(char image[][IMG_WID], int col, int row);
bool pt_mtr(char image[][IMG_WID], int col, int row);
bool pt_ctr(char image[][IMG_WID], int col, int row);
bool pt_mbl(char image[][IMG_WID], int col, int row);
bool pt_mbr(char image[][IMG_WID], int col, int row);
bool pt_bl(char image[][IMG_WID], int col, int row);

int main(int ac, char *av[])
{
	char	digits[DIG_NUM][DIG_HGT][DIG_WID];
	char	image[IMG_HGT][IMG_WID];

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
    
    print_plate(plate);    

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

    print_result(results);

}

// Testing Functions
void print_plate(char plate[IMG_HGT][IMG_WID])
{
    for (int n=0;n<IMG_HGT;n++){
	for (int i=0;i<IMG_WID;i++){
	    cout << plate[n][i];
    	}
        cout << endl;
    }
}

void analyze_cell(char plate[IMG_HGT][IMG_WID], 
                  int row, int col, 
                  int results[results_size][3], 
                  int no_test[results_size][2],
                  char digs[DIG_NUM][DIG_HGT][DIG_WID])
{
    // The following code should be added in order to make sure it is just one number, not multiple
    // If it is multiple, the character presented is probably not a number (should return ?)
    // && !(is_2(plate,col,row) || is_3(plate,col,row) ||  
    //      is_4(plate,col,row) || is_5(plate,col,row) || 
    //      is_6(plate,col,row) || is_7(plate,col,row) ||
    //      is_8(plate,col,row) || is_9(plate,col,row) ||
    //      is_0(plate,col,row))
    
    int num;

    if (is_1(plate,col,row)) {
        num = 1;
    } else if (is_2(plate,col,row)) {
	    num = 2;  
    } else if (is_3(plate,col,row)) { 
        num = 3;  
    } else if (is_4(plate,col,row)) {
	    num = 4;
    } else if (is_5(plate,col,row)) {
	    num = 5;
    } else if (is_6(plate,col,row)) { 
        num = 6; 
    } else if (is_7(plate,col,row)) {
	    num = 7;  
    } else if (is_8(plate,col,row)) {
	    num = 8; 
    } else if (is_9(plate,col,row)) {
	    num = 9;
    } else if (is_0(plate,col,row)) {
        num = 0; 
    } else {
	    num = -1;  
    }

    store_result(num,row,col,results);
    make_no_test(num,row,col,no_test,digs);
} 

void print_result(int results[results_size][3])
{
    int i=0;
    while (results[i][0] != SENTINEL){

        cout << results[i][0];
        cout << " @ " << results[i][1] << "," 
             << results[i][2] << " ";
        i++;
    }
    cout << -1 << endl;
}

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

void make_no_test(int num, int row, int col, int no_test[results_size][2], 
                  char digs[DIG_NUM][DIG_HGT][DIG_WID])
{
    int i=0;
    char target = '#';
    while (no_test[i][0] != SENTINEL){
        i++;
    }

    for (int m=0; m < DIG_HGT; m++){
        for (int n=0; n < DIG_WID; n++){
            if (digs[num][m][n] == target){
                no_test[i][0] = m + row;
                no_test[i][1] = n + col;
            }
            i++;
        }
    }
    no_test[i][0] = SENTINEL;
}

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


// Number Analysis
// Using the Point Analysis, these functions determine the actual number
bool is_1(char image[][IMG_WID], int col, int row)
{
    if (pt_bl(image,col,row) && !pt_mtr(image,col,row) 
        && pt_mtl(image,col,row) && pt_mbl(image,col,row) 
        && !pt_mbr(image,col,row)){
        return true;
    } else {
	    return false;
    }
}

bool is_2(char image[][IMG_WID], int col, int row)
{
    if (pt_bl(image,col,row) && pt_mtr(image,col,row) && 
        pt_mbl(image,col,row) && !pt_mtl(image,col,row)){
        return true;
    } else {
	    return false;
    }
}

bool is_3(char image[][IMG_WID], int col, int row)
{
    if (pt_bl(image,col,row) && !pt_mtl(image,col,row) && 
        pt_mtr(image,col,row) && !pt_mbl(image,col,row)){
	    return true;
    } else {
	    return false;
    }
}

bool is_4(char image[][IMG_WID], int col, int row)
{
    if (!pt_bl(image,col,row) && pt_mtl(image,col,row) && 
        !pt_tm(image,col,row)){
	    return true;
    } else {
	    return false;
    }
}

bool is_5(char image[][IMG_WID], int col, int row)
{
    if (pt_bl(image,col,row) && !pt_mtr(image,col,row) && 
        pt_mtl(image,col,row) && !pt_mtr(image,col,row) && 
        !pt_mbl(image,col,row)){
	    return true;
    } else {
	    return false;
    }
}

bool is_6(char image[][IMG_WID], int col, int row)
{
    if (pt_bl(image,col,row) && !pt_mtr(image,col,row) && 
        pt_mtl(image,col,row) && pt_mbl(image,col,row) && 
        pt_mbr(image,col,row)){
	    return true;
    } else {
	    return false;
    }
}

bool is_7(char image[][IMG_WID], int col, int row)
{
    if (!pt_bl(image,col,row) && !pt_mtl(image,col,row)){
	    return true;
    } else {
	    return false;
    }
}

bool is_8(char image[][IMG_WID], int col, int row)
{
    if (pt_bl(image,col,row) && pt_mtr(image,col,row) && 
        pt_mtl(image,col,row) && pt_ctr(image,col,row) && 
        pt_mbl(image,col,row)){
	    return true;
    } else {
	    return false;
    }
}

bool is_9(char image[][IMG_WID], int col, int row)
{
    if (pt_bl(image,col,row) && pt_mtl(image,col,row) && 
        pt_mtr(image,col,row) && pt_tm(image,col,row) && 
        pt_ctr(image,col,row) && !pt_mbl(image,col,row)){
	    return true;
    } else {
	    return false;
    }
}

bool is_0(char image[][IMG_WID], int col, int row)
{
    if (pt_bl(image,col,row) && pt_mtl(image,col,row) && 
        pt_mtr(image,col,row) && !pt_ctr(image,col,row)){
	    return true;
    } else {
	    return false;
    }
}

// Point Analysis
// These functions analyze to see if a "#" is present at point (row,col)
bool pt_tm(char image[][IMG_WID], int col, int row)
{
    if (image[row][col + DIG_WID/2] == '#'){
	    return true;
    } else {
	    return false;
    }
}

bool pt_mtl(char image[][IMG_WID], int col, int row)
{
    if (image[row + (DIG_HGT/2) - 1][col] == '#'){
	    return true;
    } else {
	    return false;
    }
}

bool pt_mtr(char image[][IMG_WID], int col, int row)
{
    if (image[row + (DIG_HGT/2) - 1][col + (DIG_WID-1)] == '#'){
	    return true;
    } else {
	    return false;
    }
}

bool pt_ctr(char image[][IMG_WID], int col, int row)
{
    if (image[row + (DIG_HGT/2)][col + (DIG_WID/2)] == '#'){
	    return true;
    } else {
	    return false;
    }
}

bool pt_mbl(char image[][IMG_WID], int col, int row)
{
    if (image[row + (DIG_HGT/2) + 1][col] == '#'){
	    return true;
    } else {
	    return false;
    }
} 

bool pt_mbr(char image[][IMG_WID], int col, int row)
{
    if (image[row + (DIG_HGT/2) + 1][col + (DIG_WID - 1)] == '#'){
	    return true;
    } else {
	    return false;
    }
} 

bool pt_bl(char image[][IMG_WID], int col, int row)
{
    if (image[row + (DIG_HGT-1)][col] == '#'){
	    return true;
    } else {
	    return false;
    }
} 
