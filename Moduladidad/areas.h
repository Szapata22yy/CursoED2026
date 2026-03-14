#define _USE_MATH_DEFINES
#include <math.h>
#ifndef AREAS_H
#define AREAS_H

static inline double areaCirculo(double radio) {
    return M_PI * radio * radio;
}

static inline double areaCuadrado(double lado) {
    return lado * lado;
}

#endif


