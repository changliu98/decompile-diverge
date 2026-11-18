void __cdecl njRowIDCT(int *blk)
{
  int v1; // [rsp+0h] [rbp-30h]
  int x8; // [rsp+4h] [rbp-2Ch]
  int x8a; // [rsp+4h] [rbp-2Ch]
  int x8b; // [rsp+4h] [rbp-2Ch]
  int x8c; // [rsp+4h] [rbp-2Ch]
  int x7; // [rsp+8h] [rbp-28h]
  int x7a; // [rsp+8h] [rbp-28h]
  int x7b; // [rsp+8h] [rbp-28h]
  int x6; // [rsp+Ch] [rbp-24h]
  int x6a; // [rsp+Ch] [rbp-24h]
  int x6b; // [rsp+Ch] [rbp-24h]
  int x5; // [rsp+10h] [rbp-20h]
  int x5a; // [rsp+10h] [rbp-20h]
  int x5b; // [rsp+10h] [rbp-20h]
  int x4; // [rsp+14h] [rbp-1Ch]
  int x4a; // [rsp+14h] [rbp-1Ch]
  int x4b; // [rsp+14h] [rbp-1Ch]
  int x4c; // [rsp+14h] [rbp-1Ch]
  int x3; // [rsp+18h] [rbp-18h]
  int x3a; // [rsp+18h] [rbp-18h]
  int x3b; // [rsp+18h] [rbp-18h]
  int x2; // [rsp+1Ch] [rbp-14h]
  int x2a; // [rsp+1Ch] [rbp-14h]
  int x2b; // [rsp+1Ch] [rbp-14h]
  int x1; // [rsp+20h] [rbp-10h]
  int x1a; // [rsp+20h] [rbp-10h]
  int x1b; // [rsp+20h] [rbp-10h]
  int x0; // [rsp+24h] [rbp-Ch]
  int x0a; // [rsp+24h] [rbp-Ch]
  int x0b; // [rsp+24h] [rbp-Ch]

  x1 = blk[4] << 11;
  x2 = blk[6];
  x3 = blk[2];
  x4 = blk[1];
  x5 = blk[7];
  x6 = blk[5];
  x7 = blk[3];
  if ( x7 | x6 | x5 | x4 | x3 | x2 | x1 )
  {
    x0 = (*blk << 11) + 128;
    x8 = 565 * (x5 + x4);
    x4a = 2276 * x4 + x8;
    x5a = x8 - 3406 * x5;
    x8a = 2408 * (x7 + x6);
    x6a = x8a - 799 * x6;
    x7a = x8a - 4017 * x7;
    x8b = x1 + x0;
    x0a = x0 - x1;
    x1a = 1108 * (x2 + x3);
    x2a = x1a - 3784 * x2;
    x3a = 1568 * x3 + x1a;
    x1b = x6a + x4a;
    x4b = x4a - x6a;
    x6b = x7a + x5a;
    x5b = x5a - x7a;
    x7b = x3a + x8b;
    x8c = x8b - x3a;
    x3b = x2a + x0a;
    x0b = x0a - x2a;
    x2b = (181 * (x5b + x4b) + 128) >> 8;
    x4c = (181 * (x4b - x5b) + 128) >> 8;
    *blk = (x1b + x7b) >> 8;
    blk[1] = (x2b + x3b) >> 8;
    blk[2] = (x4c + x0b) >> 8;
    blk[3] = (x6b + x8c) >> 8;
    blk[4] = (x8c - x6b) >> 8;
    blk[5] = (x0b - x4c) >> 8;
    blk[6] = (x3b - x2b) >> 8;
    blk[7] = (x7b - x1b) >> 8;
  }
  else
  {
    v1 = 8 * *blk;
    blk[7] = v1;
    blk[6] = v1;
    blk[5] = v1;
    blk[4] = v1;
    blk[3] = v1;
    blk[2] = v1;
    blk[1] = v1;
    *blk = v1;
  }
}