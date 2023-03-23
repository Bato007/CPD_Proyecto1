#include <omp.h>

#include "shared.cpp"
using namespace std;

int main( int argc, char* args[] ) {
  int numStarsAdded = 0;
  bool starExists = false;

	if (argc < 2) {
    cout << "Not enough arguments" << endl;
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
  int startDotsNum = atoi(args[1]);
  int isParallel = atoi(args[2]);
  int t_num = atoi(args[3]);
  bool quit = false;
  omp_init_lock(&starLock);

  dots.reserve(startDotsNum + 1);

  // Event handler
  SDL_Event e;

  // Creating initial star in 200, 200
  Dot* star = new Dot(200, 200);
  star->setStar();
  dots.push_back(star);
  starExists = true;

  // The dot that will be moving around on the screen
  #pragma omp parallel for num_threads(t_num) if (isParallel)
  for (int i = 1; i < startDotsNum + 1; i++) {
    int diameter = (rand() % 4 + 1) * 20;

    int random = SCREEN_WIDTH - diameter;
    int posX = rand() % random;
    int posY= rand() % random;
    // omp_in_parallel();
    Dot* newDot = createNewDot(diameter, posX, posY);

    #pragma omp critical (dots)
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
    while(SDL_PollEvent(&e) != 0) {
      //User requests quit
      if( e.type == SDL_QUIT ) { quit = true; }
    }

    starExists = false;
    #pragma omp parallel for num_threads(t_num) if (isParallel)
    for (Dot* d: dots) {
      if (d->getIsStar()) {
        starExists = true;
      }
    }

    if (!starExists) {
      // Creating star
      int random = SCREEN_WIDTH - 400;
      int posX = rand() % random;
      int posY= rand() % random;
      Dot* tempStar = new Dot(posX, posY);
      tempStar->setStar();
      dots.push_back(tempStar);
      numStarsAdded += 1;
      starExists = true;
    }

    numStarsAdded = 0;
    #pragma omp parallel for num_threads(t_num) shared(numStarsAdded) if (isParallel)
    for (size_t i = 0; i < dots.size(); i++) {
      // Move the dot
      Dot* dot = dots.at(i);
      // For every other dot
      for (size_t j = i + 1; j < dots.size(); j++) {
          Dot* otherdot = dots.at(j);

          Circle* otherDotCollider = otherdot -> getCollider(otherdot);
          Circle* currentCollider = dot -> getCollider(dot);

          dot->move(otherDotCollider);
          otherdot->move(currentCollider);

          if (checkCollision(otherDotCollider, currentCollider) || checkCollision(currentCollider, otherDotCollider)) {
            /*
            If there is no velocity on x and y, it means one of them is the star
            */
            if (dot->getIsStar() || otherdot->getIsStar()) {
              Dot* currentDot = otherdot;
              Dot* star = dot;
              if (otherdot -> getIsStar()) {
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

                omp_set_lock(&starLock);
                  if (!dots.at(i)->getErased() && !dots.at(i)->getErased()) {
                    dots.at(i)->setErase();
                    dots.at(j)->setErase();
                    deletedDotsIndex.push_back(j);
                    deletedDotsIndex.push_back(i);
                    newDots.push_back(childDot1);
                    newDots.push_back(childDot2);

                    if (numStarsAdded == 0 && !starExists) {
                      // Creating star
                      int random = SCREEN_WIDTH - 400;
                      int posX = rand() % random;
                      int posY= rand() % random;
                      Dot* tempStar = new Dot(posX, posY);
                      tempStar->setStar();
                      dots.push_back(tempStar);
                      numStarsAdded += 1;
                    }
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
                if (!dots.at(i)->getErased() && !dots.at(i)->getErased()) {
                  dots.at(i)->setErase();
                  dots.at(j)->setErase();

                  deletedDotsIndex.push_back(j);
                  deletedDotsIndex.push_back(i);
                  if (newDiameter <= MAX_DIAMETER) {
                    newDots.push_back(newDot);
                  }
                }
              }
            }
          }
      }
    }

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

    if (!starExists) {
      // Creating star
      int random = SCREEN_WIDTH - 400;
      int posX = rand() % random;
      int posY= rand() % random;
      Dot* tempStar = new Dot(posX, posY);
      tempStar->setStar();
      dots.push_back(tempStar);
      numStarsAdded += 1;
      starExists = true;
    }

    dots.clear();
    dots.insert(dots.begin(), newDots.begin(), newDots.end());
    deletedDotsIndex.clear();
    newDots.clear();

    // Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    // Render objects
    for (size_t i = 0; i < dots.size(); i++) {
      Dot* dot = dots.at(i);
      dot->render();
    }

    if (dots.size() == 1) { quit = true; }

    // Update screen
    SDL_RenderPresent( gRenderer );

    fps = 1.f / ((float)(newtime - oldtime) / 1000.f);
    cout << "FPS:" << fps << endl;
  }

	// Free resources and close SDL
	close();

	return 0;
}
