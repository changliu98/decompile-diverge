#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

#include <float.h>

static void fht16(float A[16])
{
 float alpha, beta, beta2, alpha1, alpha2, y1, y2, y3;
 alpha = A[0];
 beta = A[1];
 beta2 = A[2];
 alpha1 = A[3];
 alpha2 = alpha + beta;
 y1 = alpha - beta;
 y2 = beta2 + alpha1;
 y3 = beta2 - alpha1;
 A[0] = alpha2 + y2;
 A[2] = alpha2 - y2;
 A[1] = y1 + y3;
 A[3] = y1 - y3;
 alpha = A[4];
 beta = A[5];
 beta2 = A[6];
 alpha1 = A[7];
 alpha2 = alpha + beta;
 y1 = alpha - beta;
 y2 = beta2 + alpha1;
 y3 = beta2 - alpha1;
 A[4] = alpha2 + y2;
 A[6] = alpha2 - y2;
 A[5] = y1 + y3;
 A[7] = y1 - y3;
 alpha = A[8];
 beta = A[9];
 beta2 = A[10];
 alpha1 = A[11];
 alpha2 = alpha + beta;
 y1 = alpha - beta;
 y2 = beta2 + alpha1;
 y3 = beta2 - alpha1;
 A[8] = alpha2 + y2;
 A[10] = alpha2 - y2;
 A[9] = y1 + y3;
 A[11] = y1 - y3;
 alpha = A[12];
 beta = A[13];
 beta2 = A[14];
 alpha1 = A[15];
 alpha2 = alpha + beta;
 y1 = alpha - beta;
 y2 = beta2 + alpha1;
 y3 = beta2 - alpha1;
 A[12] = alpha2 + y2;
 A[14] = alpha2 - y2;
 A[13] = y1 + y3;
 A[15] = y1 - y3;
 alpha = A[0];
 beta = A[4];
 A[0] = alpha + beta;
 A[4] = alpha - beta;
 alpha = A[2];
 beta = A[6];
 A[2] = alpha + beta;
 A[6] = alpha - beta;
 alpha = A[1];
 beta = 0.707106769f*(A[5] + A[7]);
 beta2 = 0.707106769f*(A[5] - A[7]);
 A[1] = alpha + beta;
 A[5] = alpha - beta;
 alpha = A[3];
 A[3] = alpha + beta2;
 A[7] = alpha - beta2;
 alpha = A[8];
 beta = A[12];
 A[8] = alpha + beta;
 A[12] = alpha - beta;
 alpha = A[10];
 beta = A[14];
 A[10] = alpha + beta;
 A[14] = alpha - beta;
 alpha = A[9];
 beta = 0.707106769f*(A[13] + A[15]);
 beta2 = 0.707106769f*(A[13] - A[15]);
 A[9] = alpha + beta;
 A[13] = alpha - beta;
 alpha = A[11];
 A[11] = alpha + beta2;
 A[15] = alpha - beta2;
 alpha = A[0];
 beta = A[8];
 A[0] = alpha + beta;
 A[8] = alpha - beta;
 alpha = A[4];
 beta = A[12];
 A[4] = alpha + beta;
 A[12] = alpha - beta;
 alpha1 = A[1];
 alpha2 = A[7];
 beta = A[9] * 0.923879504f + A[15] * 0.382683426f;
 beta2 = A[9] * 0.382683426f - A[15] * 0.923879504f;
 A[1] = alpha1 + beta;
 A[9] = alpha1 - beta;
 A[7] = alpha2 + beta2;
 A[15] = alpha2 - beta2;
 alpha1 = A[10] * 0.707106769f;
 alpha2 = A[14] * 0.707106769f;
 beta = alpha1 + alpha2;
 beta2 = alpha1 - alpha2;
 alpha1 = A[2];
 alpha2 = A[6];
 A[2] = alpha1 + beta;
 A[10] = alpha1 - beta;
 A[6] = alpha2 + beta2;
 A[14] = alpha2 - beta2;
 alpha1 = A[3];
 alpha2 = A[5];
 beta = A[11] * 0.382683426f + A[13] * 0.923879504f;
 beta2 = A[11] * 0.923879504f - A[13] * 0.382683426f;
 A[3] = alpha1 + beta;
 A[11] = alpha1 - beta;
 A[5] = alpha2 + beta2;
 A[13] = alpha2 - beta2;
}
