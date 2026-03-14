#include <stdio.h>
#include "areas.h"
#include "volumenes.h"

int main(void) {
    double r = 2.5;
    double l = 3.0;

    printf("area del circulo (r=%.2f): %.4f\n", r, areaCirculo(r));
    printf("area del cuadrado (l=%.2f): %.4f\n", l, areaCuadrado(l));
    printf("volumen de la esfera (r=%.2f): %.4f\n", r, volumenEsfera(r));
    printf("volumen del cubo (l=%.2f): %.4f\n", l, volumenCubo(l));

    return 0;
}
