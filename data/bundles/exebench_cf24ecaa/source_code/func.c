#include <math.h>

void dot_matrixT_vector_ddd(double *matrix, double *in, double *out) {
  out[0] = matrix[0]*in[0] + matrix[3]*in[1] + matrix[6]*in[2];
  out[1] = matrix[1]*in[0] + matrix[4]*in[1] + matrix[7]*in[2];
  out[2] = matrix[2]*in[0] + matrix[5]*in[1] + matrix[8]*in[2];
}
