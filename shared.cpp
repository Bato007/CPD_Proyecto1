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

/// @brief checks if two circles have a collision
/// @param a the first circle
/// @param b the second circle
/// @return if there was a collision or not
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

/// @brief calculates the distance elevated by 2
/// @param x1 position x of first circle
/// @param y1 position y of first circle
/// @param x2 position x of second circle
/// @param y2 position y of second circle
/// @return the distance with pow 2 (d^2 = (x2 - x1)^2 + (y2 - y1)^2)
double distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

/// @brief init all SDL2 related variables and libraries
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

/// @brief loads all textures to memory
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

/// @brief frees the memory and cleans the variables of SDL
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

/// @brief creates a new dot in the screen
/// @param diameter the diameter of the dot
/// @param posX intial X position of the dot
/// @param posY intial Y position of the dot
/// @return a new dot with assigned values
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

/// @brief creates a new dot in the screen
/// @param diameter the diameter of the dot
/// @param posX intial X position of the dot
/// @param posY intial Y position of the dot
/// @param velX intial X velocity of the dot
/// @param velY intial Y velocity of the dot
/// @return a new dot with assigned values
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

// Class functions
// --- LTexture ---

/// @brief Creates a new default texture
LTexture::LTexture() {
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

/// @brief Free memory of the texture
LTexture::~LTexture() {
	// Deallocate
	free();
}

/// @brief Loads to memory a texture
/// @param path the relative path to the texture 
/// @return if the texture was opened
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

/// @brief Free memory of the texture
void LTexture::free() {
	// Free texture if it exists
	if(mTexture != NULL) {
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

/// @brief Renders the screen on the 
/// @param x 
/// @param y 
/// @param clip 
/// @param angle 
/// @param center 
/// @param flip 
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

/// @brief Gets the width of the texture
/// @return The width of the texture
int LTexture::getWidth() {
	return mWidth;
}

/// @brief Gets the height of the texture
/// @return The height of the texture
int LTexture::getHeight() {
	return mHeight;
}

/// @brief Constructor of dot
/// @param posX initial X position of dot
/// @param posY initial Y position of dot
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

/// @brief Constructor of dot
/// @param x maximum value of X velocity
/// @param y maximum value of Y velocity
/// @param posX initial X position of dot 
/// @param posY intial Y position of dot
/// @param texture the texture of the dot
/// @param diameter the diameter of the dot
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

/// @brief Moves a dot on the screen
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

/// @brief Makes the move of a dot based on another circle
/// @param circle the other circle that can affect current dot
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

/// @brief Renders the dot on the screen on certain position
void Dot::render() {
  // Show the dot
	dotTexture->render(mPosX - mCollider->r, mPosY - mCollider->r);
}

/// @brief Moves the collider to current position of the dot
void Dot::shiftColliders() {
	//Align collider to center of dot
	mCollider->x = mPosX;
	mCollider->y = mPosY;
}

/// @brief Gets the collider of the other dot
/// @param otherdot the dot that will return it's collider
/// @return the collider of other dot
Circle* Dot::getCollider(Dot *otherdot) {
	return otherdot->mCollider;
}
