#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
  public:
    Circle();
    Circle(int, double, double);

    static int getRadius() {return radius;};
    static double getXPos() {return xPosition;};
    static double getYPos() {return yPosition;};

    static void reverseXVelocity() {xVelocity = -xVelocity;};
    static void reverseYVelocity() {yVelocity = -yVelocity;};

    void render();

  private:
    static int radius;
    static double xPosition;
    static double yPosition;

    static double xVelocity;
    static double yVelocity;
};

#endif
