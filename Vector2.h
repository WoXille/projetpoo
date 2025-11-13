#pragma once

#include <iostream>
#include <math.h>



class Vector2 {
private:
  float x;
  float y; 
public:
  void init(float x, float y) {
    this->x = x;
    this->y = y;
  }
  float getX() const {
    return x;
  }
  float getY() const {
    return y;
  }
  float norm() const {
    return sqrt(x * x + y * y);
  }
  float dot(const Vector2 &r) const {
    return x * r.x + y * r.y;
  }
  float cross(const Vector2 &r) const {
    return (x * r.y) - (y * r.x);
  }
};