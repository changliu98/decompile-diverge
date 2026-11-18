void __cdecl Mat4_affine_inv(float *mat)
{
  int v; // [rsp+0h] [rbp-14h]
  int va; // [rsp+0h] [rbp-14h]
  int vb; // [rsp+0h] [rbp-14h]
  unsigned int v_4; // [rsp+4h] [rbp-10h]
  unsigned int v_8; // [rsp+8h] [rbp-Ch]

  v = *((_DWORD *)mat + 1);
  mat[1] = mat[4];
  *((_DWORD *)mat + 4) = v;
  va = *((_DWORD *)mat + 2);
  mat[2] = mat[8];
  *((_DWORD *)mat + 8) = va;
  vb = *((_DWORD *)mat + 6);
  mat[6] = mat[9];
  *((_DWORD *)mat + 9) = vb;
  *(float *)&v_4 = (float)(mat[9] * mat[14]) + (float)((float)(mat[1] * mat[12]) + (float)(mat[5] * mat[13]));
  *(float *)&v_8 = (float)(mat[10] * mat[14]) + (float)((float)(mat[2] * mat[12]) + (float)(mat[6] * mat[13]));
  *((_DWORD *)mat + 12) = _mm_cvtsi128_si32((__m128i)COERCE_UNSIGNED_INT(
                                                       (float)(mat[8] * mat[14])
                                                     + (float)((float)(*mat * mat[12]) + (float)(mat[4] * mat[13])))) ^ 0x80000000;
  *((_DWORD *)mat + 13) = _mm_cvtsi128_si32((__m128i)v_4) ^ 0x80000000;
  *((_DWORD *)mat + 14) = _mm_cvtsi128_si32((__m128i)v_8) ^ 0x80000000;
}