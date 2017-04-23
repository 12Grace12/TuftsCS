#include <iostream>

using namespace std;

const int SENTINEL = 0;
const int array_space = 30001;

double avg(int array[]);
int over_avg(int array[], double average);

int main()
{
    int nums[array_space];
    int i = 0;
    
    // This do-loop takes in values until it finds the SENTINEL
    do {
    	cin >> nums[i];
	i++;
	if (nums[0] == 0){
	    cout  << 0 << endl;
	    return 0;
	}
	if (i == array_space+1){
	    cerr << "too much input" << endl;
	    return 1;
	}
    } while (nums[i-1] != SENTINEL);
	
    double average = avg(nums);
    int	over_average = over_avg(nums,average); 
    cout << over_average << endl;   
}

/////////////////////////////////////////////////////
// / / / / / / / / / Functions / / / / / / / / / / //
/////////////////////////////////////////////////////

// This function takes in an array of numbers, sums each 
//    element, and then determines the average
double avg(int nums[])
{
    double sum = 0;
    for (int i=0;i<array_space;i++){
	if (nums[i]==SENTINEL){
	    return (sum/i);
	} else {
	    sum += nums[i];
	}
    }

    return (sum/array_space);
}

// This function takes in an array of integers and an average
// It goes through each element of the array and checks if
//     it is greater than the average
// If it is, it adds one to a counter
int over_avg(int nums[], double avg)
{
    int elem_over = 0;
    for (int i=0;i<array_space;i++){
	if (nums[i]==SENTINEL){
	    return elem_over;
	} else if (nums[i]>avg){
	    elem_over++;
	}
    }
    return elem_over;
}
