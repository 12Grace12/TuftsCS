#include <iostream>
#include "Fish.h"
#include "FishTank.h"

using namespace std;

const bool singleStep = false;
const int  fps = 30;

int main()
{
    string tank_test;
    int    tank_height, tank_width;
    cin >> tank_test >> tank_height >> tank_width;
    
    // test that first word was in fact tank
    if (tank_test != "tank"){
	return 1;
    }
    
    // create a fish and tank instance
    Fish fishy;
    FishTank tanky(tank_height, tank_width);
    
    // read in fish and draw them until an error in readFish()
    // (such as EOF, bad fish input, etc)
    while(fishy.readFish()){
	tanky.addFish(fishy);
	fishy.draw(&tanky);
    }
    
    // simulate motion in tank
    tanky.simulate(singleStep, fps);
    return 0;
}
