#pragma once

#include "Vector2.h"
#include <iostream>

class Point2 {
private:
    float x;
    float y;

public:
    // Constructeurs
    Point2();               // équivalent de Point2_init
    Point2(float a, float b); // équivalent de Point2_init_with_xy

    // Accesseurs
    float getX() const;
    float getY() const;

    // Mutateurs
    void setX(float a);
    void setY(float b);

    // Affichage
    void print() const;
};
