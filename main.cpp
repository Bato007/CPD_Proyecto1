/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */

#include "Headers/Dot.h"
using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//The application time based timer
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

//The dot that will move around on the screen

//Starts up SDL and creates window
bool init();

//Circle/Circle collision detector
bool checkCollision( Dot& a, Dot& b );

//Calculates distance squared between two points
double distanceSquared( int x1, int y1, int x2, int y2 );

bool checkCollision( Circle* a, Circle* b )
{
	//Calculate total radius squared
	int totalRadiusSquared = a->r + b->r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    //If the distance between the centers of the circles is less than the sum of their radii
    if( distanceSquared( a->x, a->y, b->x, b->y ) < ( totalRadiusSquared ) )
    {
        //The circles have collided
        return true;
    }

    //If not
    return false;
}

double distanceSquared( int x1, int y1, int x2, int y2 )
{
	cout << "y1 " << y1 << "   x1 " << x1 << "\n";
	cout << "y2 " << y2 << "   x2 " << x2 << "\n";
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;
LTexture dot20Texture;
LTexture dot40Texture;
LTexture dot80Texture;
LTexture dot160Texture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


Dot::Dot(int x, int y, int posX, int posY, LTexture* texture)
{
    //Initialize the offsets
    mPosX = posX;
    mPosY = posY;

    //Set collision circle size
    mCollider = new Circle();
    mCollider->r = DOT_WIDTH / 2;
    mCollider->x = posX;
    mCollider->y = posY;

    //Initialize the velocity
    mVelX = x;
    mVelY = y;

		// Initialize texture
		dotTexture = texture;
}

void Dot::move(Circle* circle)
{
    //Move the dot left or right
    mPosX += mVelX;
	shiftColliders();

    //If the dot collided or went too far to the left or right
	if( ( mPosX - mCollider->r < 0 ) || ( mPosX + mCollider->r > SCREEN_WIDTH ) || checkCollision( mCollider, circle ) )
    {
		cout << "Entra en el if\n";
        //Move back
        mVelX = -mVelX;
    	// mPosX += mVelX;
		shiftColliders();
    }

    //Move the dot up or down
    mPosY += mVelY;
	shiftColliders();

    //If the dot collided or went too far up or down
    if( ( mPosY - mCollider->r < 0 ) || ( mPosY + mCollider->r > SCREEN_HEIGHT ) || checkCollision( mCollider, circle ) )
    {
		cout << "Entra en el segundo if\n";
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

void Dot::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mVelX = -mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
		mVelY = -mVelY;
    }

		shiftColliders();
}

void Dot::render()
{
    //Show the dot
	dotTexture->render( mPosX - mCollider->r, mPosY - mCollider->r );
}

Circle* Dot::getCollider(Dot *otherdot)
{
	cout << "[GET COLIDER] " << otherdot->mCollider->r << " -------- " << otherdot->mCollider->y << endl;
	return otherdot->mCollider;
}


void Dot::shiftColliders()
{
	//Align collider to center of dot
	mCollider->x = mPosX;
	mCollider->y = mPosY;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !dot20Texture.loadFromFile( "./dotsTextures/dot20.bmp" )	)
	{
		printf( "Failed to load dot20 texture!\n" );
		success = false;
	}

	if( !dot40Texture.loadFromFile( "./dotsTextures/dot40.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !dot80Texture.loadFromFile( "./dotsTextures/dot80.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !dot160Texture.loadFromFile( "./dotsTextures/dot160.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	dot20Texture.free();
	dot40Texture.free();
	dot80Texture.free();
	dot160Texture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if (argc < 2) {
		printf("No se han ingresado suficientes argumentos");
		exit(-1);
	}
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			vector<Dot*> dots;

			//The dot that will be moving around on the screen
			for (int i=0; i<atoi(args[1]); i++) {
				int size = rand() % 4;
				switch (size)
				{
				case 0:
					/* 20 dot */
					/* Speed: [7, 8]  */
					dots.push_back(new Dot(rand() % 2 + 7, rand() % 2 + 7, i*100 + 20, i*100 + 20, &dot20Texture));
					break;
				case 1:
					/* 40 dot */
					/* Speed: [5, 6]  */
					dots.push_back(new Dot(rand() % 2 + 5, rand() % 2 + 5, i*100 + 20, i*100 + 20, &dot40Texture));
					break;
				case 2:
					/* 80 dot */
					/* Speed: [3, 4]  */
					dots.push_back(new Dot(rand() % 2 + 3, rand() % 2 + 3, i*100 + 20, i*100 + 20, &dot80Texture));
					break;
				case 3:
					/* 160 dot */
					/* Speed: [1, 2]  */
					dots.push_back(new Dot(rand() % 2 + 1, rand() % 2 + 1, i*100 + 20, i*100 + 20, &dot160Texture));
					break;
				
				default:
					break;
				}
				// dots.push_back(new Dot(rand() % 5 + 1, rand() % 5 + 1, i*100 + 20, i*100 + 20));
			}
			// Dot otherdot(rand() % 5 + 1, rand() % 5 + 1, 100 + 20, 100 + 20);

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}


				for (size_t i = 0; i < dots.size(); i++)
				{
					//Move the dot
					Dot* dot = dots[i];
					// For every other dot
					for (size_t j = i + 1; j < dots.size(); j++)
					{
						Dot* otherdot = dots[j];
						dot->move(otherdot -> getCollider(otherdot));
					}
					if (i + 1 == dots.size()) {
						dot->move();
					}
				}
				


				// for (Dot* dot: dots) {
				// 	dot->move(otherDot);
				// }
				// dotAB.move();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render objects
				for (Dot* dot: dots) {
					dot->render();
				}
				// otherdot.render();
				// dotAB.render();

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}