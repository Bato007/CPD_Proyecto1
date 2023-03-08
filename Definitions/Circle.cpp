#include "../Headers/Circle.h"

Circle::Circle() = default;

Circle::Circle(int radius, double xPos, double yPos) {
  this->radius = radius;
  this->xPosition = xPos;
  this->yPosition = yPos;
}

void Circle::render() {
  
}
