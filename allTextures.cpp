// Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <omp.h>
#include <iterator>
#include <string>
#include <stdlib.h>     /* srand, rand */

#include "Headers/Dot.h"
using namespace std;

// Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const int MAX_DIAMETER = 700;

vector<Dot*> dots;
vector<Dot*> newDots;
vector<int> deletedDotsIndex;
omp_lock_t starLock;

// The application time based timer
class LTimer {
  public:
  // Initializes variables
  LTimer();

  // The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();

  // Gets the timer's time
  Uint32 getTicks();

  // Checks the status of the timer
  bool isStarted();
  bool isPaused();

  private:
  // The clock time when the timer started
  Uint32 mStartTicks;

  // The ticks stored when the timer was paused
  Uint32 mPausedTicks;

  // The timer status
  bool mPaused;
  bool mStarted;
};

// The dot that will move around on the screen

// Starts up SDL and creates window
bool init();

// Circle/Circle collision detector
bool checkCollision( Dot& a, Dot& b );

// Calculates distance squared between two points
double distanceSquared( int x1, int y1, int x2, int y2 );

bool checkCollision( Circle* a, Circle* b ) {
    // int totalRadiusSquared = a->r + b->r;
	// totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;
	// Calculate total radius squared
	int totalRadiusSquared = b->r;
    if ( a->r < b->r) {
        totalRadiusSquared = a->r;
    }
    totalRadiusSquared *= 2 * totalRadiusSquared;
  // If the distance between the centers of the circles is less than the sum of their radii
//   cout << "distanceSquared( a->x, a->y, b->x, b->y ): "  << distanceSquared( a->x, a->y, b->x, b->y ) << "\n";
  if (distanceSquared( a->x, a->y, b->x, b->y ) < (totalRadiusSquared)) {
//   cout << "distanceSquared( a->x, a->y, b->x, b->y ): "  << distanceSquared( a->x, a->y, b->x, b->y ) << "   " << totalRadiusSquared << "\n";
    return true;
  }

  return false;
}

double distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
    // cout << "deltaX: "  << deltaX << "    deltaY: " << deltaY << "\n";
	return deltaX*deltaX + deltaY*deltaY;
}

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

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

void Dot::print() {
	cout << "PosX: " << mPosX << ", PosY: " << mPosY << ", VelX: " << mVelX << ", VelY: " << mVelY << endl;
	cout << "Collider info: colliderX: " << mCollider->x << ", colliderY: " << mCollider->y << endl;
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

void Dot::render() {
  // Show the dot
	dotTexture->render(mPosX - mCollider->r, mPosY - mCollider->r);
}

Circle* Dot::getCollider(Dot *otherdot) {
	return otherdot->mCollider;
}


void Dot::shiftColliders() {
	//Align collider to center of dot
	mCollider->x = mPosX;
	mCollider->y = mPosY;
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
    case 280:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot280Texture, diameter));
    case 300:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot300Texture, diameter));
    case 320:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot320Texture, diameter));
    case 340:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot340Texture, diameter));
    case 360:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot360Texture, diameter));
    case 380:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot380Texture, diameter));
    case 400:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot400Texture, diameter));
    case 420:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot420Texture, diameter));
    case 440:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot440Texture, diameter));
    case 460:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot460Texture, diameter));
    case 480:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot480Texture, diameter));
    case 500:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot500Texture, diameter));
    case 520:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot520Texture, diameter));
    case 540:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot540Texture, diameter));
    case 560:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot560Texture, diameter));
    case 580:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot580Texture, diameter));
    case 600:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot600Texture, diameter));
    case 620:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot620Texture, diameter));
    case 640:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot640Texture, diameter));
    case 660:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot660Texture, diameter));
    case 680:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot680Texture, diameter));
    case MAX_DIAMETER:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(velX, velY,
				newPosX,
				newPosY,
				&dot700Texture, diameter));
    default:
      /* 100 dot */
      /* Speed: [2, 3]  */
        return nullptr;
  }
}

// Overload to set random velocities
Dot* createNewDot(int diameter, int posX, int posY) {
	int newPosX = min(max(diameter / 2, posX), SCREEN_WIDTH - (diameter / 2));
	int newPosY = min(max(diameter / 2, posY), SCREEN_HEIGHT - (diameter / 2));
  switch (diameter) {
    case 20:
      /* 20 dot */
      /* Speed: [7, 8]  */
      return (new Dot(rand() % 2 + 1.6, rand() % 2 + 1.6,
				newPosX,
				newPosY,
				&dot20Texture, diameter));
    case 40:
      /* 40 dot */
      /* Speed: [5, 6]  */
      return (new Dot(rand() % 2 + 1.4, rand() % 2 + 1.4,
				newPosX,
				newPosY,
				&dot40Texture, diameter));
    case 60:
      /* 60 dot */
      /* Speed: [4, 5]  */
      return (new Dot(rand() % 2 + 1.2, rand() % 2 + 1.2,
				newPosX,
				newPosY,
				&dot60Texture, diameter));
    case 80:
      /* 80 dot */
      /* Speed: [3, 4]  */
      return (new Dot(rand() % 2 + 1.1, rand() % 2 + 1.1,
				newPosX,
				newPosY,
				&dot80Texture, diameter));
    case 100:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 1, rand() % 2 + 1,
				newPosX,
				newPosY,
				&dot100Texture, diameter));
    case 120:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.9, rand() % 2 + 0.9,
				newPosX,
				newPosY,
				&dot120Texture, diameter));
    case 140:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.8, rand() % 2 + 0.8,
				newPosX,
				newPosY,
				&dot140Texture, diameter));
    case 160:
      /* 160 dot */
      /* Speed: [1, 2]  */
      return (new Dot(rand() % 2 + 0.7, rand() % 2 + 0.7,
				newPosX,
				newPosY,
				&dot160Texture, diameter));
    case 180:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.6, rand() % 2 + 0.6,
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
    case 280:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.38, rand() % 2 + 0.38,
				newPosX,
				newPosY,
				&dot280Texture, diameter));
    case 300:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.36, rand() % 2 + 0.36,
				newPosX,
				newPosY,
				&dot300Texture, diameter));
    case 320:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.35, rand() % 2 + 0.35,
				newPosX,
				newPosY,
				&dot320Texture, diameter));
    case 340:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.33, rand() % 2 + 0.33,
				newPosX,
				newPosY,
				&dot340Texture, diameter));
    case 360:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.32, rand() % 2 + 0.32,
				newPosX,
				newPosY,
				&dot360Texture, diameter));
    case 380:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.31, rand() % 2 + 0.31,
				newPosX,
				newPosY,
				&dot380Texture, diameter));
    case 400:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.3, rand() % 2 + 0.3,
				newPosX,
				newPosY,
				&dot400Texture, diameter));
    case 420:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.24, rand() % 2 + 0.24,
				newPosX,
				newPosY,
				&dot420Texture, diameter));
    case 440:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.23, rand() % 2 + 0.23,
				newPosX,
				newPosY,
				&dot440Texture, diameter));
    case 460:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.22, rand() % 2 + 0.22,
				newPosX,
				newPosY,
				&dot460Texture, diameter));
    case 480:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.21, rand() % 2 + 0.21,
				newPosX,
				newPosY,
				&dot480Texture, diameter));
    case 500:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.2, rand() % 2 + 0.2,
				newPosX,
				newPosY,
				&dot500Texture, diameter));
    case 520:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.18, rand() % 2 + 0.18,
				newPosX,
				newPosY,
				&dot520Texture, diameter));
    case 540:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.16, rand() % 2 + 0.16,
				newPosX,
				newPosY,
				&dot540Texture, diameter));
    case 560:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.14, rand() % 2 + 0.14,
				newPosX,
				newPosY,
				&dot560Texture, diameter));
    case 580:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.12, rand() % 2 + 0.12,
				newPosX,
				newPosY,
				&dot580Texture, diameter));
    case 600:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.1, rand() % 2 + 0.1,
				newPosX,
				newPosY,
				&dot600Texture, diameter));
    case 620:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.1, rand() % 2 + 0.1,
				newPosX,
				newPosY,
				&dot620Texture, diameter));
    case 640:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.1, rand() % 2 + 0.1,
				newPosX,
				newPosY,
				&dot640Texture, diameter));
    case 660:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.1, rand() % 2 + 0.1,
				newPosX,
				newPosY,
				&dot660Texture, diameter));
    case 680:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.1, rand() % 2 + 0.1,
				newPosX,
				newPosY,
				&dot680Texture, diameter));
    case MAX_DIAMETER:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return (new Dot(rand() % 2 + 0.1, rand() % 2 + 0.1,
				newPosX,
				newPosY,
				&dot700Texture, diameter));
      
    default:
      /* 100 dot */
      /* Speed: [2, 3]  */
      return nullptr;
  }
}

void makeMoves(int numberThreads) {
  int numStarsAdded = 0;

  #pragma omp parallel for
  for (size_t i = 0; i < dots.size(); i++) {
    // Move the dot
    Dot* dot = dots[i];
    // For every other dot
    for (size_t j = i + 1; j < dots.size(); j++) {
      
      Dot* otherdot = dots[j];

      Circle* otherDotCollider = otherdot -> getCollider(otherdot);
      Circle* currentCollider = dot -> getCollider(dot);

      dot->move(otherDotCollider);
      otherdot->move(currentCollider);

      if (checkCollision(otherDotCollider, currentCollider) || checkCollision(currentCollider, otherDotCollider)) {
        /* MAX_DIAMETER
        If there is no velocity on x and y, it means one of them is the star
        */
        if (((dot -> getVelX() == 0 && dot -> getVelY() == 0) || (otherdot -> getVelX() == 0 && otherdot -> getVelY() == 0))) {
          Dot* currentDot = otherdot;
          Dot* star = dot;
          if (otherdot -> getVelX() == 0 && otherdot -> getVelY() == 0) {
            currentDot = dot;
            star = otherdot;
          }

          if (currentDot -> getCollider(currentDot) -> r >= star -> getCollider(star) -> r) {
            int newDiameter = currentDot -> getCollider(currentDot) -> r;

            /*
            Getting an available texture
            */
            if (newDiameter % 20 != 0) {
              newDiameter += 10;
            }

            int newPosX = currentDot->getPosX(), newPosY = currentDot->getPosY();
            if (newPosX + newDiameter >= SCREEN_WIDTH) {
              newPosX = newPosX - (newPosX + newDiameter - SCREEN_WIDTH - 5);
            }

            if (newPosY + newDiameter >= SCREEN_HEIGHT) {
              newPosY = newPosY - (newPosY + newDiameter - SCREEN_HEIGHT - 5);
            }

            // Creating two new dots
            Dot* childDot1 = createNewDot(newDiameter, newPosX, newPosY);
            Dot* childDot2 = createNewDot(newDiameter, newPosX + newDiameter, newPosY + newDiameter);

            // Creating star
            int random = SCREEN_WIDTH - 400;
            int posX = rand() % random;
            int posY= rand() % random;
            Dot* newStar = new Dot(posX, posY);

            // Super critical section
            omp_set_lock(&starLock);
              deletedDotsIndex.push_back(j);
              deletedDotsIndex.push_back(i);
              newDots.push_back(childDot1);
              newDots.push_back(childDot2);

              if (numStarsAdded == 0) {
                newDots.push_back(newStar);
                numStarsAdded++;
              }
            omp_unset_lock(&starLock);
          }
        } else if (otherDotCollider -> r !=  currentCollider -> r) {
          int posX, posY;
          if (otherDotCollider->r > currentCollider->r) {
            posX = otherdot->getPosX();
            posY = otherdot->getPosY();
          } else {
            posX = dot->getPosX();
            posY = dot->getPosY();
          }

          int newDiameter = (otherDotCollider -> r + currentCollider -> r) * 2;

          int newRadius = newDiameter / 2;

          int newSpeedX = ((dot->dotWidth / 2) * dot->getVelX() + (otherdot->dotWidth / 2) * otherdot->getVelX()) / newRadius;
          int newSpeedY = ((dot->dotWidth / 2) * dot->getVelY() + (otherdot->dotWidth / 2) * otherdot->getVelY()) / newRadius;

          Dot* newDot = createNewDot(newDiameter, posX, posY, newSpeedX, newSpeedY);

          #pragma omp critical
          {
            deletedDotsIndex.push_back(j);
            deletedDotsIndex.push_back(i);
            if (newDiameter <= 700) {
                newDots.push_back(newDot);
            }
          }
        } 
      }
    }
  }
}

int main( int argc, char* args[] ) {
	if (argc < 2) {
    cout << "No se han ingresado suficientes argumentos" << endl;
		exit(-1);
	}

	// Start up SDL and create window
	if(!init()) {
    cout << "Failed to initialize" << endl;
    exit(-1);
	}

  //Load media
  if(!loadMedia()) {
    cout << "Failed to load media" << endl;
    exit(-1);
  }

  // Main loop flag
  bool quit = false;
  omp_init_lock(&starLock);

  // Event handler
  SDL_Event e;

  // Creating initial star in 200, 200
  dots.push_back(new Dot(200, 200));

  // The dot that will be moving around on the screen
  #pragma omp parallel for 
  for (int i=0; i < atoi(args[1]); i++) {
    unsigned int myseed = omp_get_thread_num();
    int diameter = (rand() % 2 + 1) * 20;
    int radio = diameter / 2;

    int randomX = SCREEN_WIDTH - radio;
    int randomY = SCREEN_HEIGHT - radio;
    int posX = (rand() % randomX) + radio;
    int posY= (rand() % randomY) + radio;
    Dot* newDot = createNewDot(diameter, posX, posY);

    #pragma omp critical(dots)
    dots.push_back(newDot);
  }

  Uint32 oldtime = 0;
  Uint32 newtime = 0;
  float fps = 0.0f;

  // While application is running
  while(!quit) {
    oldtime = newtime;
    newtime = SDL_GetTicks();
    // Handle events on queue
    while(SDL_PollEvent( &e ) != 0) {
      //User requests quit
      if( e.type == SDL_QUIT ) {
        quit = true;
      }
    }

    makeMoves(omp_get_num_threads());

    for (size_t i = 0; i < dots.size(); i++) {
      int found = 0;

      // Search for index
      for (size_t j = 0; j < deletedDotsIndex.size(); j++) {
        if (deletedDotsIndex.at(j) == (int)i) {
          found = 1;
          break;
        }
      }

      // Do not insert
      if (found == 1) { continue; }
      newDots.push_back(dots.at(i));
    }

    dots.clear();
    dots.insert(dots.begin(), newDots.begin(), newDots.end());
    deletedDotsIndex.clear();
    newDots.clear();

    // Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    // Render objects
    for (Dot* dot: dots) {
      dot->render();
    }

    // Update screen
    SDL_RenderPresent( gRenderer );

    newDots.clear();
    deletedDotsIndex.clear();

    fps = 1.f / ((float)(newtime - oldtime) / 1000.f);
    // cout << "FPS:" << fps << endl;
  }

	// Free resources and close SDL
	close();

	return 0;
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
