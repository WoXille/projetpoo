#include "Vector2.h"

void Vector2::init(float x, float y) {
    this->x = x;
    this->y = y;
}   
float Vector2::getX() const {
    return x;
}

float Vector2::getY() const {
    return y;
}
float Vector2::norm() const {
    return sqrt(x * x + y * y);
}
float Vector2::dot(const Vector2 &r) const {
    return x * r.x + y * r.y;
}
float Vector2::cross(const Vector2 &r) const {
    return (x * r.y) - (y * r.x);
}
