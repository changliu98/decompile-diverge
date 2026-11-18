void __cdecl fht16(float *A)
{
  float y1, alpha2, alpha1, beta2, beta;
  float alpha, betaa, beta2a, alpha1a;
  float alphaa, betab, beta2b, alpha1b;
  float alphab, betac, beta2c, alpha1c;
  float alphac, betad, alphad, betae, alphae, betaf, beta2d, alphaf;
  float alphag, betag, alphah, betah, alphai, betai, beta2e, alphaj;
  float alphak, betaj, alphal, betak, alpha1d, alpha2a, betal, beta2f;
  float alpha1e, alpha2b, betam, beta2g, alpha1f, alpha2c;
  float alpha1g, alpha2d, betan, beta2h;

  // Stage 1: 4-point transforms on blocks of 4
  beta = A[1];
  beta2 = A[2];
  alpha1 = A[3];
  alpha2 = *A + beta;
  y1 = *A - beta;
  *A = alpha2 + (float)(beta2 + alpha1);
  A[2] = alpha2 - (float)(beta2 + alpha1);
  A[1] = y1 + (float)(beta2 - alpha1);
  A[3] = y1 - (float)(beta2 - alpha1);

  alpha = A[4];
  betaa = A[5];
  beta2a = A[6];
  alpha1a = A[7];
  A[4] = (float)(alpha + betaa) + (float)(beta2a + alpha1a);
  A[6] = (float)(alpha + betaa) - (float)(beta2a + alpha1a);
  A[5] = (float)(alpha - betaa) + (float)(beta2a - alpha1a);
  A[7] = (float)(alpha - betaa) - (float)(beta2a - alpha1a);

  alphaa = A[8];
  betab = A[9];
  beta2b = A[10];
  alpha1b = A[11];
  A[8] = (float)(alphaa + betab) + (float)(beta2b + alpha1b);
  A[10] = (float)(alphaa + betab) - (float)(beta2b + alpha1b);
  A[9] = (float)(alphaa - betab) + (float)(beta2b - alpha1b);
  A[11] = (float)(alphaa - betab) - (float)(beta2b - alpha1b);

  alphab = A[12];
  betac = A[13];
  beta2c = A[14];
  alpha1c = A[15];
  A[12] = (float)(alphab + betac) + (float)(beta2c + alpha1c);
  A[14] = (float)(alphab + betac) - (float)(beta2c + alpha1c);
  A[13] = (float)(alphab - betac) + (float)(beta2c - alpha1c);
  A[15] = (float)(alphab - betac) - (float)(beta2c - alpha1c);

  // Stage 2: 8-point transforms on blocks of 8
  alphac = *A;
  betad = A[4];
  *A = *A + betad;
  A[4] = alphac - betad;

  alphad = A[2];
  betae = A[6];
  A[2] = alphad + betae;
  A[6] = alphad - betae;

  alphae = A[1];
  betaf = 0.70710677f * (float)(A[5] + A[7]);
  beta2d = 0.70710677f * (float)(A[5] - A[7]);
  A[1] = alphae + betaf;
  A[5] = alphae - betaf;

  alphaf = A[3];
  A[3] = alphaf + beta2d;
  A[7] = alphaf - beta2d;

  alphag = A[8];
  betag = A[12];
  A[8] = alphag + betag;
  A[12] = alphag - betag;

  alphah = A[10];
  betah = A[14];
  A[10] = alphah + betah;
  A[14] = alphah - betah;

  alphai = A[9];
  betai = 0.70710677f * (float)(A[13] + A[15]);
  beta2e = 0.70710677f * (float)(A[13] - A[15]);
  A[9] = alphai + betai;
  A[13] = alphai - betai;

  alphaj = A[11];
  A[11] = alphaj + beta2e;
  A[15] = alphaj - beta2e;

  // Stage 3: 16-point transform
  alphak = *A;
  betaj = A[8];
  *A = *A + betaj;
  A[8] = alphak - betaj;

  alphal = A[4];
  betak = A[12];
  A[4] = alphal + betak;
  A[12] = alphal - betak;

  alpha1d = A[1];
  alpha2a = A[7];
  betal = (float)(A[9] * 0.9238795f) + (float)(0.38268343f * A[15]);
  beta2f = (float)(A[9] * 0.38268343f) + (float)(-(0.9238795f * A[15]));
  A[1] = alpha1d + betal;
  A[9] = alpha1d - betal;
  A[7] = alpha2a + beta2f;
  A[15] = alpha2a - beta2f;

  alpha1e = 0.70710677f * A[10];
  alpha2b = 0.70710677f * A[14];
  betam = alpha1e + alpha2b;
  beta2g = alpha1e - alpha2b;

  alpha1f = A[2];
  alpha2c = A[6];
  A[2] = alpha1f + betam;
  A[10] = alpha1f - betam;
  A[6] = alpha2c + beta2g;
  A[14] = alpha2c - beta2g;

  alpha1g = A[3];
  alpha2d = A[5];
  betan = (float)(A[11] * 0.38268343f) + (float)(0.9238795f * A[13]);
  beta2h = (float)(A[11] * 0.9238795f) + (float)(-(0.38268343f * A[13]));
  A[3] = alpha1g + betan;
  A[11] = alpha1g - betan;
  A[5] = alpha2d + beta2h;
  A[13] = alpha2d - beta2h;
}