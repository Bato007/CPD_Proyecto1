#include "shared.cpp"
using namespace std;

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

  // Event handler
  SDL_Event e;

  // Creating initial star in 200, 200
  dots.push_back(new Dot(200, 200));

  // The dot that will be moving around on the screen
  for (int i=0; i<atoi(args[1]); i++) {
    int diameter = (rand() % 4 + 1) * 20;

    int random = SCREEN_WIDTH - diameter;
    int posX = rand() % random;
    int posY= rand() % random;
    dots.push_back(createNewDot(diameter, posX, posY));
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
            /*
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
                dots.erase(dots.begin() + j);
                dots.erase(dots.begin() + i);

                int newDiameter = currentDot -> getCollider(currentDot) -> r;

                /*
                Getting an available texture
                */
                if (newDiameter % 20 != 0) {
                  newDiameter += 10;
                }
                newDiameter = getDiameter(newDiameter);

                int newPosX = currentDot->getPosX(), newPosY = currentDot->getPosY();
                if (newPosX + newDiameter >= SCREEN_WIDTH) {
                  newPosX = newPosX - (newPosX + newDiameter - SCREEN_WIDTH - 5);
                }

                if (newPosY + newDiameter >= SCREEN_HEIGHT) {
                  newPosY = newPosY - (newPosY + newDiameter - SCREEN_HEIGHT - 5);
                }

                // Creating two new dots
                dots.push_back(createNewDot(newDiameter, newPosX, newPosY));
                dots.push_back(createNewDot(newDiameter, newPosX + newDiameter, newPosY + newDiameter));

                // Creating star
                int random = SCREEN_WIDTH - 400;
                int posX = rand() % random;
                int posY= rand() % random;
                dots.push_back(new Dot(posX, posY));
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
              dots.erase(dots.begin() + j);
              dots.erase(dots.begin() + i);

              int newDiameter = (otherDotCollider -> r + currentCollider -> r) * 2;
              newDiameter = getDiameter(newDiameter);

              int newRadius = newDiameter / 2;

              int newSpeedX = ((dot->dotWidth / 2) * dot->getVelX() + (otherdot->dotWidth / 2) * otherdot->getVelX()) / newRadius;
              int newSpeedY = ((dot->dotWidth / 2) * dot->getVelY() + (otherdot->dotWidth / 2) * otherdot->getVelY()) / newRadius;

              dots.push_back(createNewDot(newDiameter, posX, posY, newSpeedX, newSpeedY));
            }
          }

        

      }
    }

    // Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    // Render objects
    for (Dot* dot: dots) {
      dot->render();
    }

    // Update screen
    SDL_RenderPresent( gRenderer );

    fps = 1.f / ((float)(newtime - oldtime) / 1000.f);
    printf("FPS: %f\n", fps);
  }

	// Free resources and close SDL
	close();

	return 0;
}
