#include <stdarg.h>

template <int Dim = 2, class Coordinate_t = int>
class PositionDim: public Position {
 public:
  // Constructor con lista variable de parámetros
  PositionDim(int sz, ...) {
    va_list vl;
    va_start(vl, sz);

    for(int d = 0; d < Dim; d++) {
      Coordinates[d] = va_arg(vl, Coor_t);
    }
    
    va_end(vl);
  }
  Coor_t operator[](unsigned int) const;
 private:
  Coor_t Coordinates[Dim];
};