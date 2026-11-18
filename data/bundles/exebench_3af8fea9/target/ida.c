int __cdecl mpeg3video_idctrow(short *blk)
{
  short v2; // [rsp+0h] [rbp-36h]
  int x8; // [rsp+2h] [rbp-34h]
  int x8a; // [rsp+2h] [rbp-34h]
  int x8b; // [rsp+2h] [rbp-34h]
  int x8c; // [rsp+2h] [rbp-34h]
  int x7; // [rsp+6h] [rbp-30h]
  int x7a; // [rsp+6h] [rbp-30h]
  int x7b; // [rsp+6h] [rbp-30h]
  int x6; // [rsp+Ah] [rbp-2Ch]
  int x6a; // [rsp+Ah] [rbp-2Ch]
  int x6b; // [rsp+Ah] [rbp-2Ch]
  int x5; // [rsp+Eh] [rbp-28h]
  int x5a; // [rsp+Eh] [rbp-28h]
  int x5b; // [rsp+Eh] [rbp-28h]
  int x4; // [rsp+12h] [rbp-24h]
  int x4a; // [rsp+12h] [rbp-24h]
  int x4b; // [rsp+12h] [rbp-24h]
  int x4c; // [rsp+12h] [rbp-24h]
  int x3; // [rsp+16h] [rbp-20h]
  int x3a; // [rsp+16h] [rbp-20h]
  int x3b; // [rsp+16h] [rbp-20h]
  int x2; // [rsp+1Ah] [rbp-1Ch]
  int x2a; // [rsp+1Ah] [rbp-1Ch]
  int x2b; // [rsp+1Ah] [rbp-1Ch]
  int x1; // [rsp+1Eh] [rbp-18h]
  int x1a; // [rsp+1Eh] [rbp-18h]
  int x1b; // [rsp+1Eh] [rbp-18h]
  int x0; // [rsp+22h] [rbp-14h]
  int x0a; // [rsp+22h] [rbp-14h]
  int x0b; // [rsp+22h] [rbp-14h]

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
    return 1;
  }
  else
  {
    v2 = 8 * *blk;
    blk[7] = v2;
    blk[6] = v2;
    blk[5] = v2;
    blk[4] = v2;
    blk[3] = v2;
    blk[2] = v2;
    blk[1] = v2;
    *blk = v2;
    return 0;
  }
}