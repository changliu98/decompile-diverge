#include <math.h>

#include <assert.h>

static void cspline2bezier(double out[4], const double in[4])
{
 const double m[4][4] = {
  { 1., 1., 0., 0., },
  { 0., 1./ 3., 0., 0., },
  { 0., 0., 1., 1., },
  { 0., 0., -1./3., 0., },
 };

 for (int i = 0; i < 4; i++) {

  out[i] = 0.;

  for (int j = 0; j < 4; j++)
   out[i] += m[j][i] * in[j];
 }
}
