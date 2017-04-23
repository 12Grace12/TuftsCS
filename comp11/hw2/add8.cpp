//                                                                                   
//   add8.cpp                                                                        
//   purpose: add eight user-input doubles                                           
//        by: Benjamin Tanen                                                         
//      date: 1/23/14                                                                
//                                                                                   

#include <iostream>

using namespace std;

int main()
{

    double sum = 0;
    double num;
    int i = 0;

    cout << "Enter eight numbers (Use either spaces/enters to break-up the numbers): ";
    
    while (i < 8) {
    	cin >> num;
    	sum = num + sum;
    	i++;
    }

    cout << "Total sum is " << sum << endl;
    
}
