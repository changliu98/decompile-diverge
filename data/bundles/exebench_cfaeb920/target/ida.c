void __cdecl mtxTranspose(float *mtx, const float *src)
{
  int tmp; // [rsp+0h] [rbp-14h]
  int tmpa; // [rsp+0h] [rbp-14h]
  int tmpb; // [rsp+0h] [rbp-14h]
  int tmpc; // [rsp+0h] [rbp-14h]
  int tmpd; // [rsp+0h] [rbp-14h]
  int tmpe; // [rsp+0h] [rbp-14h]

  *mtx = *src;
  mtx[5] = src[5];
  mtx[10] = src[10];
  mtx[15] = src[15];
  tmp = *((_DWORD *)src + 4);
  mtx[4] = src[1];
  *((_DWORD *)mtx + 1) = tmp;
  tmpa = *((_DWORD *)src + 8);
  mtx[8] = src[2];
  *((_DWORD *)mtx + 2) = tmpa;
  tmpb = *((_DWORD *)src + 12);
  mtx[12] = src[3];
  *((_DWORD *)mtx + 3) = tmpb;
  tmpc = *((_DWORD *)src + 9);
  mtx[9] = src[6];
  *((_DWORD *)mtx + 6) = tmpc;
  tmpd = *((_DWORD *)src + 13);
  mtx[13] = src[7];
  *((_DWORD *)mtx + 7) = tmpd;
  tmpe = *((_DWORD *)src + 14);
  mtx[14] = src[11];
  *((_DWORD *)mtx + 11) = tmpe;
}