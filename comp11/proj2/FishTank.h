#ifndef FISHTANK_H
#define FISHTANK_H

#include <string>
using std::string;

class FishTank {
	public:
		FishTank();
		/* Function:  FishTank() [Constructor]
		   Purpose:   This is the constructor of the fish tank class.
			      By calling it, a fish tank is created, which can
			      be used by in SimFishy program
		   Arguments: None
		   Returns:   Nothing
		   Effects:   Creates a Fish Tank for SimFishy
		   Notes:     This is the null constructor for a new fish tank */
		FishTank(int hgt, int wid);
		/* Function:  FishTank(hgt, wid) [Constructor]
		   Purpose:   This is the non-null constructor of the fish tank 
			      class. By calling it, a fish tank is created with 
			      the specific height and width specified, which can
			      be used by in SimFishy program
		   Arguments: a height and width (both integers)
		   Returns:   Nothing
		   Effects:   Creates a Fish Tank for SimFishy
		   Notes:     This is the non-null constructor for a new fish 
			      tank. It creates a fish tank of a specific size */
		void setHeight(int hgt);
		/* Function:  setHeight()
		   Purpose:   This allows users to change the height
			      of the fish tank
		   Arguments: A new height for the fish (int)
		   Returns:   Nothing
		   Effects:   Changes the height of the fish tank
		   Notes:     None */
		void setWidth(int wid);
		/* Function:  setWidth()
		   Purpose:   This allows users to change the width
			      of the fish tank
		   Arguments: A new width for the fish (int)
		   Returns:   Nothing
		   Effects:   Changes the width of the fish tank
		   Notes:     None */
		int  getHeight();
		/* Function:  getHeight()
		   Purpose:   This function is for getting the height 
			      of a fish tank
		   Arguments: None
		   Returns:   The height of the fish (int)
		   Effects:   None
		   Notes:     None */
		int  getWidth();
		/* Function:  getWidth()
		   Purpose:   This function is for getting the width 
			      of a fish tank
		   Arguments: None
		   Returns:   The width of the fish (int)
		   Effects:   None
		   Notes:     None */
		int  getMaxFish();
		/* Function:  getMaxFish()
		   Purpose:   This function is for getting the maximum 
			      amount of fish allowed in a fish tank
		   Arguments: None
		   Returns:   The max number of fish allowed (int)
		   Effects:   None
		   Notes:     None */
		int  getNumFish();
		/* Function:  getMaxFish()
		   Purpose:   This function is for getting the current 
			      number of fish in a fish tank
		   Arguments: None
		   Returns:   The current number of fish (int)
		   Effects:   None
		   Notes:     None */
		bool addFish(Fish f);
		/* Function:  addFish()
		   Purpose:   This function is used for adding a fish
			      to the "fish_holder" array. These fish
			      can then be used/drawn in the tank.
		   Arguments: A new fish (Fish)
		   Returns:   True, if successful. False, if not (ex: too many
			      fish) (Boolean)
		   Effects:   A new fish is added to the fish_holder array
		   Notes:     None */
		void clearTank();
		/* Function:  clearTank()
		   Purpose:   This function clears the tank of all
			      previously drawn fish elements
		   Arguments: None
		   Returns:   Nothing
		   Effects:   Clears all drawn fish from tank
		   Notes:     None */
		void showTank();
		/* Function:  showTank()
		   Purpose:   This function draws out the tank and
			      everything that is drawn within it
			      (ie fish)
		   Arguments: None
		   Returns:   Nothing
		   Effects:   Draws out the tank & its contents
		   Notes:     None */
		void UpdateAt(int row, int col, char newChar);
		/* Function:  UpdateAt()
		   Purpose:   This function updates the contents/character
			      in a certain specified element of the tank 
			      image with a new character.
		   Arguments: A new character (char) and a location to
			      put it (row/col) (both integers)
		   Returns:   Nothing
		   Effects:   This will change the character in a certain
			      specified tank array element.
		   Notes:     This is used within the Fish.draw() function */
		void simulate(bool singleStep, int fps);
		/* Function:  simulate()
		   Purpose:   This is the function that holds the other main
			      functions that provides the simulation for the
			      tank and the fishes within it.
		   Arguments: The frames-per-second of the animation (int)
			      and a boolean to determine if singleStep should
			      be enabled (the animation only continues when the
			      user presses enter). Both of these are defined/
			      declared in the SimFishy file.
		   Returns:   Nothing
		   Effects:   This is the running simulation of the fish tank
			      Using draw()/showTank(), it shows the fish
			      moving around within the tank.
		   Notes:     This function holds many other functions,
			      both from the fish tank and the fishes
			      contained within it.
			      This function will run endlessly until
			      it is stopped by the user
			      (force quitting, ctrl - c) */
	
	private:
		static const int  MAX_FISH = 40;
		static const int  MAX_HGT = 50;
		static const int  MAX_WID = 200;
		
		int height, width;
		int num_fish;
		Fish fish_holder[MAX_FISH];
		char tank_image[MAX_HGT][MAX_WID];
		void clear_screen();
		/* Function:  clear_screan()
		   Purpose:   This clears the screen for the animation
		   Arguments: None
		   Returns:   Nothing
		   Effects:   Clears the screen of a previously drawn tank
		   Notes:     None */
		void home_cursor();
		/* Function:  home_cursor()
		   Purpose:   This sets the cursor of the terminal back
			      to its home position.
		   Arguments: None
		   Returns:   Nothing
		   Effects:   Sets the cursor back to home.
		   Notes:     None */
		
};

#endif
