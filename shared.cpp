// Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */

#include "Headers/Dot.h"
using namespace std;

// Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const int MAX_DIAMETER = 700;

// Dots controll variables
vector<Dot*> dots;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Scene textures
LTexture gDotTexture;
LTexture dot20Texture;
LTexture dot40Texture;
LTexture dot60Texture;
LTexture dot80Texture;
LTexture dot100Texture;
LTexture dot120Texture;
LTexture dot140Texture;
LTexture dot160Texture;
LTexture dot180Texture;
LTexture dot200Texture;
LTexture dot220Texture;
LTexture dot240Texture;
LTexture dot260Texture;
LTexture dot280Texture;
LTexture dot300Texture;
LTexture dot320Texture;
LTexture dot340Texture;
LTexture dot360Texture;
LTexture dot380Texture;
LTexture dot400Texture;
LTexture dot420Texture;
LTexture dot440Texture;
LTexture dot460Texture;
LTexture dot480Texture;
LTexture dot500Texture;
LTexture dot520Texture;
LTexture dot540Texture;
LTexture dot560Texture;
LTexture dot580Texture;
LTexture dot600Texture;
LTexture dot620Texture;
LTexture dot640Texture;
LTexture dot660Texture;
LTexture dot680Texture;
LTexture dot700Texture;
LTexture starTexture;

// Declaration of functions
bool checkCollision(Circle* a, Circle* b);
double distanceSquared(int x1, int y1, int x2, int y2);
bool init();
bool loadMedia();
void close();
Dot* createNewDot(int diameter, int posX, int posY);
Dot* createNewDot(int diameter, int posX, int posY, int velX, int velY);

bool checkCollision(Circle* a, Circle* b) {
	// Calculate total radius squared
	int totalRadiusSquared = a->r + b->r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

  // If the distance between the centers of the circles is less than the sum of their radii
  if (distanceSquared(a->x, a->y, b->x, b->y) < (totalRadiusSquared)) {
    return true;
  }

  return false;
}

int getDiameter(int newDiameter) {
	if (newDiameter > 260) {
		newDiameter = 320;
	} else if (newDiameter > 400) {
		newDiameter = 400;
	} else if (newDiameter > 500) {
		newDiameter = 500;
	} else if (newDiameter > 700) {
		newDiameter = 700;
	}
	return newDiameter;
}

double distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

bool init() {
	// Init de SDL
	if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
    cout << "[ERROR]: SDL didn't init" << SDL_GetError() << endl;
    return false;
	}

	// Set texture filtering to linear
  if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    cout << "[Warning]: Linear Textures are not enabled" << endl;
  }

  // Create window
  gWindow = SDL_CreateWindow("CPD Proyecto 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(gWindow == NULL) {
    cout << "[ERROR]: Window couldn't be created" << SDL_GetError() << endl;
    return false;
  }

  // Create vsynced renderer for window
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(gRenderer == NULL) {
    cout << "[ERROR]: Render couldn't be init" << SDL_GetError() << endl;
    return false;
  }

  // Initialize renderer color
  SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init( imgFlags ) & imgFlags)) {
    cout << "[ERROR]: SDL_Image didn't init" << IMG_GetError() << endl;
    return false;
  }

	return true;
}

bool loadMedia() {
	// Loading success flag
	bool success = true;

	// Load dot texture
	if (!dot20Texture.loadFromFile("./dotsTextures/dot20.png")) {
    cout << "[ERROR]: Failed to load dot20 texture" << endl;
		success = false;
	}

	if (!dot40Texture.loadFromFile("./dotsTextures/dot40.png")){
    cout << "[ERROR]: Failed to load dot40 texture" << endl;
		success = false;
	}

	if (!dot60Texture.loadFromFile("./dotsTextures/dot60.png")) {
    cout << "[ERROR]: Failed to load dot60 texture" << endl;
		success = false;
	}

	if (!dot80Texture.loadFromFile( "./dotsTextures/dot80.png")){
    cout << "[ERROR]: Failed to load dot80 texture" << endl;
		success = false;
	}
  
	if (!dot100Texture.loadFromFile("./dotsTextures/dot100.png")) {
    cout << "[ERROR]: Failed to load dot100 texture" << endl;
		success = false;
	}
  
	if (!dot120Texture.loadFromFile("./dotsTextures/dot120.png")) {
    cout << "[ERROR]: Failed to load dot120 texture" << endl;
		success = false;
	}

	if (!dot140Texture.loadFromFile("./dotsTextures/dot140.png")) {
    cout << "[ERROR]: Failed to load dot140 texture" << endl;
		success = false;
	}

	if (!dot160Texture.loadFromFile("./dotsTextures/dot160.png")) {
    cout << "[ERROR]: Failed to load dot160 texture" << endl;
		success = false;
	}
  
	if (!dot180Texture.loadFromFile("./dotsTextures/dot180.png")) {
    cout << "[ERROR]: Failed to load dot180 texture" << endl;
		success = false;
	}

	if (!dot200Texture.loadFromFile("./dotsTextures/dot200.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
  
	if (!dot220Texture.loadFromFile("./dotsTextures/dot220.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}

	if (!dot240Texture.loadFromFile("./dotsTextures/dot240.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}

	if (!dot260Texture.loadFromFile("./dotsTextures/dot260.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}

	if (!dot280Texture.loadFromFile("./dotsTextures/dot280.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot300Texture.loadFromFile("./dotsTextures/dot300.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot320Texture.loadFromFile("./dotsTextures/dot320.png")) {
    cout << "[ERROR]: Failed to load dot250 texture" << endl;
		success = false;
	}
	if (!dot340Texture.loadFromFile("./dotsTextures/dot340.png")) {
    cout << "[ERROR]: Failed to load dot250 texture" << endl;
		success = false;
	}

	if (!dot360Texture.loadFromFile("./dotsTextures/dot360.png")) {
    cout << "[ERROR]: Failed to load dot250 texture" << endl;
		success = false;
	}

	if (!dot380Texture.loadFromFile("./dotsTextures/dot380.png")) {
    cout << "[ERROR]: Failed to load dot250 texture" << endl;
		success = false;
	}


	if (!dot400Texture.loadFromFile("./dotsTextures/dot400.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot420Texture.loadFromFile("./dotsTextures/dot420.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot440Texture.loadFromFile("./dotsTextures/dot440.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot460Texture.loadFromFile("./dotsTextures/dot460.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot480Texture.loadFromFile("./dotsTextures/dot480.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}

	if (!dot500Texture.loadFromFile("./dotsTextures/dot500.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot520Texture.loadFromFile("./dotsTextures/dot520.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot540Texture.loadFromFile("./dotsTextures/dot540.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot560Texture.loadFromFile("./dotsTextures/dot560.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot580Texture.loadFromFile("./dotsTextures/dot580.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot600Texture.loadFromFile("./dotsTextures/dot600.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot620Texture.loadFromFile("./dotsTextures/dot620.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot640Texture.loadFromFile("./dotsTextures/dot640.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot660Texture.loadFromFile("./dotsTextures/dot660.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}
	if (!dot680Texture.loadFromFile("./dotsTextures/dot680.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}

	if (!dot700Texture.loadFromFile("./dotsTextures/dot700.png")) {
    cout << "[ERROR]: Failed to load dot200 texture" << endl;
		success = false;
	}

	if (!starTexture.loadFromFile("./dotsTextures/star.png")) {
    cout << "[ERROR]: Failed to load star texture" << endl;
		success = false;
	}
	return success;
}

void close() {
	// Free loaded images
	dot20Texture.free();
	dot40Texture.free();
	dot60Texture.free();
	dot80Texture.free();
	dot100Texture.free();
	dot120Texture.free();
	dot140Texture.free();
	dot160Texture.free();
	dot180Texture.free();
	dot200Texture.free();
	dot220Texture.free();
	dot240Texture.free();
	dot260Texture.free();
	dot280Texture.free();
	dot300Texture.free();
	dot320Texture.free();
	dot340Texture.free();
	dot360Texture.free();
	dot380Texture.free();
	dot400Texture.free();
	dot420Texture.free();
	dot440Texture.free();
	dot460Texture.free();
	dot480Texture.free();
	dot500Texture.free();
	dot520Texture.free();
	dot540Texture.free();
	dot560Texture.free();
	dot580Texture.free();
	dot600Texture.free();
	dot620Texture.free();
	dot640Texture.free();
	dot660Texture.free();
	dot680Texture.free();
	dot700Texture.free();
  starTexture.free();

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

Dot* createNewDot(int diameter, int posX, int posY) {
	int newPosX = min(max(diameter / 2, posX), SCREEN_WIDTH - (diameter / 2));
	int newPosY = min(max(diameter / 2, posY), SCREEN_HEIGHT - (diameter / 2));
  switch (diameter) {
    case 20:
      /* 20 dot */
      /* Speed: [7, 8]  */
      return (new Dot(rand() % 2 + 2.6, rand() % 2 + 3,
				newPosX,
				newPosY,
				&dot20Texture, diameter));
    case 40:
      /* 40 dot */
      /* Speed: [5, 6]  */
      return (new Dot(rand() % 2 + 2.4, rand() % 2 + 2.8,
				newPosX,
				newPosY,
				&dot40Texture, diameter));
    case 60:
      /* 60 dot */
      /* Speed: [4, 5]  */
      return (new Dot(rand() % 2 + 2.2, rand() % 2 + 2.4,
				newPosX,
				newPosY,
				&dot60Texture, diameter));
    case 80:
      /* 80 dot */
      /* Speed: [3, 4]  */
      return (new Dot(rand() % 2 + 2, rand() % 2 + 3,
				newPosX,
				newPosY,
				&dot80Texture, diameter));
    case 100:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 1.8, rand() % 2 + 2.5,
				newPosX,
				newPosY,
				&dot100Texture, diameter));
    case 120:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 1.6, rand() % 2 + 2,
				newPosX,
				newPosY,
				&dot120Texture, diameter));
    case 140:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 1.4, rand() % 2 + 1.8,
				newPosX,
				newPosY,
				&dot140Texture, diameter));
    case 160:
      /* 160 dot */
      /* Speed: [1, 2]  */
      return (new Dot(rand() % 2 + 1.2, rand() % 2 + 1.5,
				newPosX,
				newPosY,
				&dot160Texture, diameter));
    case 180:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 1, rand() % 2 + 1,
				newPosX,
				newPosY,
				&dot180Texture, diameter));
    case 200:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.5, rand() % 2 + 0.5,
				newPosX,
				newPosY,
				&dot200Texture, diameter));
    case 220:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.4, rand() % 2 + 0.4,
				newPosX,
				newPosY,
				&dot220Texture, diameter));
    case 240:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.35, rand() % 2 + 0.35,
				newPosX,
				newPosY,
				&dot240Texture, diameter));
    case 260:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.4, rand() % 2 + 0.4,
				newPosX,
				newPosY,
				&dot260Texture, diameter));
    case 320:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.35, rand() % 2 + 0.35,
				newPosX,
				newPosY,
				&dot320Texture, diameter));
    case 400:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.3, rand() % 2 + 0.3,
				newPosX,
				newPosY,
				&dot400Texture, diameter));
    case 500:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.2, rand() % 2 + 0.2,
				newPosX,
				newPosY,
				&dot500Texture, diameter));
    case MAX_DIAMETER:
    default:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.1, rand() % 2 + 0.1,
				newPosX,
				newPosY,
				&dot700Texture, diameter));
  }
}

// Overload to set defined velocities
Dot* createNewDot(int diameter, int posX, int posY, int velX, int velY) {
	int newPosX = min(max(diameter / 2, posX), SCREEN_WIDTH - (diameter / 2));
	int newPosY = min(max(diameter / 2, posY), SCREEN_HEIGHT - (diameter / 2));
  switch (diameter) {
    case 20:
      /* 20 dot */
      /* Speed: [7, 8]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot20Texture, diameter));
    case 40:
      /* 40 dot */
      /* Speed: [5, 6]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot40Texture, diameter));
    case 60:
      /* 60 dot */
      /* Speed: [4, 5]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot60Texture, diameter));
    case 80:
      /* 80 dot */
      /* Speed: [3, 4]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot80Texture, diameter));
    case 100:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot100Texture, diameter));
    case 120:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot120Texture, diameter));
    case 140:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot140Texture, diameter));
    case 160:
      /* 160 dot */
      /* Speed: [1, 2]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot160Texture, diameter));
    case 180:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot180Texture, diameter));
    case 200:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot200Texture, diameter));
    case 220:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot220Texture, diameter));
    case 240:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot240Texture, diameter));
    case 260:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot260Texture, diameter));
    case 320:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot320Texture, diameter));
    case 400:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot400Texture, diameter));
    case 500:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot500Texture, diameter));
    case MAX_DIAMETER:
    default:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot700Texture, diameter));
  }
}

// Class functions
LTexture::LTexture() {
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	// Deallocate
	free();
}

bool LTexture::loadFromFile(string path) {
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL) {
    cout << "Unable to load image" << path.c_str() << "! SDL_Image Error: " << IMG_GetError() << endl;
	} else {
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL) {
      cout << "Unable to create texture from" << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
		} else {
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free() {
	// Free texture if it exists
	if(mTexture != NULL) {
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	// Set clip rendering dimensions
	if(clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}

Dot::Dot(int posX, int posY) {
  // Initialize the offsets
  mPosX = posX;
  mPosY = posY;

  // Initialize size
  dotWidth = 100;
  dotHeight = 100;

  // Set collision circle size
  mCollider = new Circle();
  mCollider->r = dotWidth / 2;
  mCollider->x = posX;
  mCollider->y = posY;

  // Initialize the velocity
  mVelX = 0;
  mVelY = 0;

  // Initialize texture
  dotTexture = &starTexture;
}

Dot::Dot(int x, int y, int posX, int posY, LTexture* texture, int diameter) {
  // Initialize the offsets
  mPosX = posX;
  mPosY = posY;

  // Initialize size
  dotWidth = diameter;
  dotHeight = diameter;

  // Set collision circle size
  mCollider = new Circle();
  mCollider->r = dotWidth / 2;
  mCollider->x = posX;
  mCollider->y = posY;

  // Initialize the velocity
  mVelX = max(1, x);
  mVelY = max(1, y);

  // Initialize texture
  dotTexture = texture;
}

void Dot::move() {
  // Move the dot left or right
  mPosX += mVelX;

  // If the dot went too far to the left or right
  if( ( mPosX - (dotWidth / 2) < 0 ) || ( mPosX + (dotWidth / 2) > SCREEN_WIDTH ) )
  {
    // Move back
    mVelX = -mVelX;
  }

  // Move the dot up or down
  mPosY += mVelY;

  // If the dot went too far up or down
  if((mPosY - (dotHeight / 2) < 0 ) || ( mPosY + (dotHeight / 2) > SCREEN_HEIGHT)) {
    //Move back
    mVelY = -mVelY;
  }

  shiftColliders();
}

void Dot::move(Circle* circle) {
  //Move the dot left or right
  mPosX += mVelX;
	shiftColliders();

  //If the dot collided or went too far to the left or right
	if( (mPosX - mCollider->r < 0 ) || ( mPosX + mCollider->r > SCREEN_WIDTH ) || checkCollision( mCollider, circle )) {
    //Move back
    mVelX = -mVelX;
    // mPosX += mVelX;
		shiftColliders();
  }

  //Move the dot up or down
  mPosY += mVelY;
	shiftColliders();

  //If the dot collided or went too far up or down
  if((mPosY - mCollider->r < 0) || (mPosY + mCollider->r > SCREEN_HEIGHT) || checkCollision(mCollider, circle)) {
    //Move back
    mVelY = -mVelY;
    // mPosY += mVelY;
    shiftColliders();
  }
}

void Dot::render() {
  // Show the dot
	dotTexture->render(mPosX - mCollider->r, mPosY - mCollider->r);
}

void Dot::shiftColliders() {
	//Align collider to center of dot
	mCollider->x = mPosX;
	mCollider->y = mPosY;
}

Circle* Dot::getCollider(Dot *otherdot) {
	return otherdot->mCollider;
}
