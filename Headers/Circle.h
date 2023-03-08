#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
  public:
    Circle();
    Circle(int, double, double);

    static int getRadius() {return radius;};
    static double getXPos() {return xPosition;};
    static double getYPos() {return yPosition;};

    void render();

  private:
    static int radius;
    static double xPosition;
    static double yPosition;
};

#endif
