#define _USE_MATH_DEFINES
#include <math.h>
#ifndef VOLUMENES_H
#define VOLUMENES_H

static inline double volumenEsfera(double radio) {
    return (4.0 / 3.0) * M_PI * pow(radio, 3);
}

static inline double volumenCubo(double lado) {
    return pow(lado, 3);
}

#endif 
