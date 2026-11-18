void __cdecl mtx3x3Transpose(float *mtx, const float *src)
{
  int tmp; // [rsp+0h] [rbp-14h]
  int tmpa; // [rsp+0h] [rbp-14h]
  int tmpb; // [rsp+0h] [rbp-14h]

  *mtx = *src;
  mtx[4] = src[4];
  mtx[8] = src[8];
  tmp = *((_DWORD *)src + 1);
  mtx[1] = src[3];
  *((_DWORD *)mtx + 3) = tmp;
  tmpa = *((_DWORD *)src + 2);
  mtx[2] = src[6];
  *((_DWORD *)mtx + 6) = tmpa;
  tmpb = *((_DWORD *)src + 5);
  mtx[5] = src[7];
  *((_DWORD *)mtx + 7) = tmpb;
}