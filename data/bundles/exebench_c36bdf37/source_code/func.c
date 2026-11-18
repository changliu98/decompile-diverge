#include <stdlib.h>

#include <math.h>

#include <stdio.h>

#include <string.h>

#include <inttypes.h>

#include <time.h>

#include <ctype.h>

void calcular_escala(double fmin, double fmax, double favg, double *m, double *b){

 double delta;


 if (fmin > ((1.2 * favg - fmax) / (1.2 - 1.0))){
  delta = fmax - favg;
  *m = ((1.2 - 1.0) * favg) / delta;
  *b = favg * ((fmax - 1.2 * favg) / delta);
 }

 else{
  if (favg == fmin){
   *m = 1.0;
   *b = 0;
  }
  else{
   delta = favg - fmin;
   *m = favg / delta;
   *b = (-fmin * favg) / delta;
  }
 }
}
