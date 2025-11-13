#include "Segment2.h"

IntersectionStatus Segment2::intersect(Segment2 r, Point2 &p) {
  Point2 oa = this->getOrigin(), ob = r.getOrigin();
  Vector2 da = this->getDirection(), db = r.getDirection(), dc = ob.sub(oa);

  IntersectionStatus status;
  float det = da.cross(db);
  if (det != 0.0) {
    float u, v;

    u = dc.cross(db) / det;
    v = dc.cross(da) / det;
    if ((u >= 0.0 && u <= 1.0) && (v >= 0.0 && v <= 1.0)) {
      Vector2 tmp = da.dot(u);

      p = oa.add(tmp);
      status = POINT;
    } else
      status = NON_INTERSECTING;
  } else {
    float st = dc.cross(this->getDirection());

    if (det == 0.0 && st == 0.0) { // check for collinearity
      float pj, d1, d2;

      pj = da.dot(da);
      d1 = ob.sub(oa).dot(da) / pj;
      d2 = d1 + db.dot(da) / pj;

      if (d1 >= 0.0 && d1 <= 1.0) {
        p = ob;
        status = COLINEAR_INTERSECTING;
      } else if (d2 >= 0.0 && d2 <= 1.0) {
        p = ob.add(db);
        status = COLINEAR_INTERSECTING;
      } else
        status = COLINEAR_NON_INTERSECTING;
    } else if (det == 0.0 && st != 0.0) {
      status = PARALLEL_NON_INTERSECTING;
    }
  }

  return status;
}