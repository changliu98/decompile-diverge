void __cdecl fht16(float *A)
{
  __m128i v1; // xmm1
  __m128i v2; // xmm1
  float y1; // [rsp+8h] [rbp-20h]
  float alpha2; // [rsp+Ch] [rbp-1Ch]
  float alpha2a; // [rsp+Ch] [rbp-1Ch]
  float alpha2b; // [rsp+Ch] [rbp-1Ch]
  float alpha2c; // [rsp+Ch] [rbp-1Ch]
  float alpha2d; // [rsp+Ch] [rbp-1Ch]
  float alpha1; // [rsp+10h] [rbp-18h]
  float alpha1a; // [rsp+10h] [rbp-18h]
  float alpha1b; // [rsp+10h] [rbp-18h]
  float alpha1c; // [rsp+10h] [rbp-18h]
  float alpha1d; // [rsp+10h] [rbp-18h]
  float alpha1e; // [rsp+10h] [rbp-18h]
  float alpha1f; // [rsp+10h] [rbp-18h]
  float alpha1g; // [rsp+10h] [rbp-18h]
  float beta2; // [rsp+14h] [rbp-14h]
  float beta2a; // [rsp+14h] [rbp-14h]
  float beta2b; // [rsp+14h] [rbp-14h]
  float beta2c; // [rsp+14h] [rbp-14h]
  float beta2d; // [rsp+14h] [rbp-14h]
  float beta2e; // [rsp+14h] [rbp-14h]
  float beta2f; // [rsp+14h] [rbp-14h]
  float beta2g; // [rsp+14h] [rbp-14h]
  float beta2h; // [rsp+14h] [rbp-14h]
  float beta; // [rsp+18h] [rbp-10h]
  float betaa; // [rsp+18h] [rbp-10h]
  float betab; // [rsp+18h] [rbp-10h]
  float betac; // [rsp+18h] [rbp-10h]
  float betad; // [rsp+18h] [rbp-10h]
  float betae; // [rsp+18h] [rbp-10h]
  float betaf; // [rsp+18h] [rbp-10h]
  float betag; // [rsp+18h] [rbp-10h]
  float betah; // [rsp+18h] [rbp-10h]
  float betai; // [rsp+18h] [rbp-10h]
  float betaj; // [rsp+18h] [rbp-10h]
  float betak; // [rsp+18h] [rbp-10h]
  float betal; // [rsp+18h] [rbp-10h]
  float betam; // [rsp+18h] [rbp-10h]
  float betan; // [rsp+18h] [rbp-10h]
  float alpha; // [rsp+1Ch] [rbp-Ch]
  float alphaa; // [rsp+1Ch] [rbp-Ch]
  float alphab; // [rsp+1Ch] [rbp-Ch]
  float alphac; // [rsp+1Ch] [rbp-Ch]
  float alphad; // [rsp+1Ch] [rbp-Ch]
  float alphae; // [rsp+1Ch] [rbp-Ch]
  float alphaf; // [rsp+1Ch] [rbp-Ch]
  float alphag; // [rsp+1Ch] [rbp-Ch]
  float alphah; // [rsp+1Ch] [rbp-Ch]
  float alphai; // [rsp+1Ch] [rbp-Ch]
  float alphaj; // [rsp+1Ch] [rbp-Ch]
  float alphak; // [rsp+1Ch] [rbp-Ch]
  float alphal; // [rsp+1Ch] [rbp-Ch]

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
  alphac = *A;
  betad = A[4];
  *A = *A + betad;
  A[4] = alphac - betad;
  alphad = A[2];
  betae = A[6];
  A[2] = alphad + betae;
  A[6] = alphad - betae;
  alphae = A[1];
  betaf = 0.70710677 * (float)(A[5] + A[7]);
  beta2d = 0.70710677 * (float)(A[5] - A[7]);
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
  betai = 0.70710677 * (float)(A[13] + A[15]);
  beta2e = 0.70710677 * (float)(A[13] - A[15]);
  A[9] = alphai + betai;
  A[13] = alphai - betai;
  alphaj = A[11];
  A[11] = alphaj + beta2e;
  A[15] = alphaj - beta2e;
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
  betal = (float)(A[9] * 0.9238795) + (float)(0.38268343 * A[15]);
  v1 = (__m128i)0x3F6C835Eu;
  *(float *)v1.m128i_i32 = 0.9238795 * A[15];
  beta2f = (float)(A[9] * 0.38268343) + COERCE_FLOAT(_mm_cvtsi128_si32(v1) ^ 0x80000000);
  A[1] = alpha1d + betal;
  A[9] = alpha1d - betal;
  A[7] = alpha2a + beta2f;
  A[15] = alpha2a - beta2f;
  alpha1e = 0.70710677 * A[10];
  alpha2b = 0.70710677 * A[14];
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
  betan = (float)(A[11] * 0.38268343) + (float)(0.9238795 * A[13]);
  v2 = (__m128i)0x3EC3EF15u;
  *(float *)v2.m128i_i32 = 0.38268343 * A[13];
  beta2h = (float)(A[11] * 0.9238795) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000);
  A[3] = alpha1g + betan;
  A[11] = alpha1g - betan;
  A[5] = alpha2d + beta2h;
  A[13] = alpha2d - beta2h;
}