#include "Point2.h"

// équivalent de Point2_init
Point2::Point2() {
    x = 0;
    y = 0;
}

// équivalent de Point2_init_with_xy
Point2::Point2(float a, float b){
    x = a;
    y = b;
}

// Accesseurs
float Point2::getX() const {
    return x;
}   

float Point2::getY() const {
    return y;
}   

// Mutateurs
void Point2::setX(float a) {    
    x = a;
}
void Point2::setY(float b) {    
    y = b;
}

// Affichage
void Point2::print() const {
    std::cout << "{" << x << ", " << y << "}" << std::endl; // ou "\n"
}


