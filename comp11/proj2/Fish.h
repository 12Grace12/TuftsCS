#ifndef FISH_H
#define FISH_H

#include <string>
using std::string;

class FishTank;

class Fish {
	public:
		Fish();
		/* Function:  Fish() [Constructor]
		   Purpose:   This is the constructor of the fish class.
			      By calling it, a fish is created, which can
			      be used by in SimFishy
		   Arguments: None
		   Returns:   Nothing
		   Effects:   Creates a Fish for SimFishy
		   Notes:     This is the null constructor for a new fish */
		bool   readFish();
		/* Function:  readFish()
		   Purpose:   This reads in information from the user/a data
			      file and fills in the data for a particular fish.
			      If the readFish() is successful, it returns true
			      while it returns false if the read is 
			      unsuccessful
		   Arguments: None
		   Returns:   Boolean (true if successful, false if not)
		   Effects:   Fills in information for a fish from user/cin
		   Notes:     If the function is unsuccessful (returns 
			      false), the fish that was created is still set
			      to the null/zero values from the constructor */
		string getName();
		/* Function:  getName()
		   Purpose:   This function is for getting the name of a fish
		   Arguments: None
		   Returns:   The name of the fish (string)
		   Effects:   None
		   Notes:     None */
		void   setName(string new_name);
		/* Function:  setName()
		   Purpose:   This allows users to change the name
			      of the fish
		   Arguments: A new name for the fish (string)
		   Returns:   Nothing
		   Effects:   Changes the name of the fish
		   Notes:     None */
		void   setHSpeed(float new_speed);
		/* Function:  setHSpeed()
		   Purpose:   This allows users to change the horizontal
			      speed of the fish
		   Arguments: A new horizontal speed for the fish (float)
		   Returns:   Nothing
		   Effects:   Changes the horizontal speed of the fish
		   Notes:     None */
		void   setVSpeed(float new_speed);
		/* Function:  setVSpeed()
		   Purpose:   This allows users to change the vertical
			      speed of the fish
		   Arguments: A new vertical speed for the fish (float)
		   Returns:   Nothing
		   Effects:   Changes the vertical speed of the fish
		   Notes:     None */
		void   setPos(int row, int col);
		/* Function:  setPos()
		   Purpose:   This allows users to change/set the vertical
			      and horizontal position of the fish
		   Arguments: A new row and column for the fish's position 
			      (both int)
		   Returns:   Nothing
		   Effects:   Changes the position (horizontal/vertical) 
			      of the fish
		   Notes:     None */
		int    getHeight();
		/* Function:  getHeight()
		   Purpose:   This function is for getting the height of a fish
		   Arguments: None
		   Returns:   The height of the fish (int)
		   Effects:   None
		   Notes:     None */
		int    getWidth();
		/* Function:  getWidth()
		   Purpose:   This function is for getting the width of a fish
		   Arguments: None
		   Returns:   The width of the fish (int)
		   Effects:   None
		   Notes:     None */
		void   move(int tankHeight, int tankWidth);
		/* Function:  move()
		   Purpose:   This function is used for moving the fish
			      throughout the tank, using it's current position
			      and velocity.
		   Arguments: The dimensions of the tank (tankHeight/tankWidth,
			      both integers)
		   Returns:   Nothing
		   Effects:   This will change the position of the fish.
		   Notes:     This is one of the most important functions
			      for the fish object. */
		void   draw(FishTank *p_tank);
		/* Function:  draw()
		   Purpose:   This function is used for drawing/putting the 
			      fish inside a particular tank.
		   Arguments: A pointer that points to a particular FishTank
		   Returns:   Nothing
		   Effects:   This will draw the image of the fish inside the
			      2D-array of a particular tank.
		   Notes:     This is one of the most important functions
			      for the fish object. */
	
	private:
		// maximum sizes for any particular fishtank
		static const int MAX_HGT = 30;
        	static const int MAX_WID = 60;

		// state properties
		string name;
		int    img_hgt, img_wid;
		float  pos_horz, pos_vert;
		float  speed_horz, speed_vert;
		char   image[MAX_HGT][MAX_WID];
};

#endif
