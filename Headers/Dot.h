#include "LTexture.h"

//A circle stucture
struct Circle
{
	int x, y;
	int r;
};

class Dot
{
    public:
		//The dimensions of the dot
		int dotWidth;
		int dotHeight;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Dot(int, int, int, int, LTexture*, int);

		//Moves the dot
		void move(Circle*);
		void move();


		//Shows the dot on the screen
		void render();

		int getVelX() {return mVelX;};
		int getVelY() {return mVelY;};

		int getPosX() {return mPosX;};
		int getPosY() {return mPosY;};

		//Gets collision circle
		Circle*  getCollider(Dot *otherdot);

		// Print info
		void print();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision circle
		Circle* mCollider;
    
		//Moves the collision circle relative to the dot's offset
		void shiftColliders();

		// Texture
		LTexture* dotTexture;
};
