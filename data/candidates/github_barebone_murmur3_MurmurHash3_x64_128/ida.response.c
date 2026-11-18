void __cdecl MurmurHash3_x64_128(const void *key, const int len, const uint32_t seed, void *out)
{
  uint64_t k2_0; // [rsp+8h] [rbp-E8h]
  uint64_t k1_0; // [rsp+10h] [rbp-E0h]
  const uint8_t *tail; // [rsp+18h] [rbp-D8h]
  uint64_t h2; // [rsp+48h] [rbp-A8h]
  uint64_t h2a; // [rsp+48h] [rbp-A8h]
  uint64_t h1; // [rsp+50h] [rbp-A0h]
  uint64_t h1a; // [rsp+50h] [rbp-A0h]
  int i; // [rsp+58h] [rbp-98h]
  int nblocks; // [rsp+5Ch] [rbp-94h]
  unsigned __int64 v13; // [rsp+98h] [rbp-58h]
  unsigned __int64 v14; // [rsp+A8h] [rbp-48h]
  unsigned __int64 v15; // [rsp+B8h] [rbp-38h]
  unsigned __int64 v16; // [rsp+C8h] [rbp-28h]
  unsigned __int64 v17; // [rsp+D8h] [rbp-18h]
  unsigned __int64 v18; // [rsp+E0h] [rbp-10h]
  unsigned __int64 v19; // [rsp+E0h] [rbp-10h]
  unsigned __int64 v20; // [rsp+E8h] [rbp-8h]
  unsigned __int64 v21; // [rsp+E8h] [rbp-8h]

  nblocks = len / 16;
  h1 = seed;
  h2 = seed;
  for ( i = 0; i < nblocks; ++i )
  {
    v17 = 0x87C37B91114253D5LL * *((_QWORD *)key + 2 * i);
    v16 = h1 ^ (0x4CF5AD432745937FLL * ((v17 >> 33) | (v17 << 31)));
    h1 = 5 * (((v16 >> 37) | (v16 << 27)) + h2) + 1390208809;
    v15 = 0x4CF5AD432745937FLL * *((_QWORD *)key + 2 * i + 1);
    v14 = h2 ^ (0x87C37B91114253D5LL * ((v15 >> 31) | (v15 << 33)));
    h2 = 5 * (((v14 >> 33) | (v14 << 31)) + h1) + 944331445;
  }
  tail = (const uint8_t *)key + 16 * nblocks;
  k1_0 = 0LL;
  k2_0 = 0LL;
  switch ( len & 0xF )
  {
    case 1:
      goto LABEL_19;
    case 2:
      goto LABEL_18;
    case 3:
      goto LABEL_17;
    case 4:
      goto LABEL_16;
    case 5:
      goto LABEL_15;
    case 6:
      goto LABEL_14;
    case 7:
      goto LABEL_13;
    case 8:
      goto LABEL_12;
    case 9:
      goto LABEL_11;
    case 0xA:
      goto LABEL_10;
    case 0xB:
      goto LABEL_9;
    case 0xC:
      goto LABEL_8;
    case 0xD:
      goto LABEL_7;
    case 0xE:
      goto LABEL_6;
    case 0xF:
      k2_0 = (unsigned __int64)tail[14] << 48;
LABEL_6:
      k2_0 ^= (unsigned __int64)tail[13] << 40;
LABEL_7:
      k2_0 ^= (unsigned __int64)tail[12] << 32;
LABEL_8:
      k2_0 ^= (unsigned __int64)tail[11] << 24;
LABEL_9:
      k2_0 ^= (unsigned __int64)tail[10] << 16;
LABEL_10:
      k2_0 ^= (unsigned __int64)tail[9] << 8;
LABEL_11:
      v13 = 0x4CF5AD432745937FLL * (k2_0 ^ tail[8]);
      h2 ^= 0x87C37B91114253D5LL * ((v13 >> 31) | (v13 << 33));
LABEL_12:
      k1_0 = (unsigned __int64)tail[7] << 56;
LABEL_13:
      k1_0 ^= (unsigned __int64)tail[6] << 48;
LABEL_14:
      k1_0 ^= (unsigned __int64)tail[5] << 40;
LABEL_15:
      k1_0 ^= (unsigned __int64)tail[4] << 32;
LABEL_16:
      k1_0 ^= (unsigned __int64)tail[3] << 24;
LABEL_17:
      k1_0 ^= (unsigned __int64)tail[2] << 16;
LABEL_18:
      k1_0 ^= (unsigned __int64)tail[1] << 8;
LABEL_19:
      h1 ^= 0x4CF5AD432745937FLL
          * (((0x87C37B91114253D5LL * (k1_0 ^ *tail)) >> 33) | (0x88A129EA80000000LL * (k1_0 ^ *tail)));
      break;
    default:
      break;
  }
  h2a = h2 ^ len;
  h1a = (h1 ^ len) + h2a;
  v20 = 0xC4CEB9FE1A85EC53LL
      * ((0xFF51AFD7ED558CCDLL * (h1a ^ (h1a >> 33))) ^ ((0xFF51AFD7ED558CCDLL * (h1a ^ (h1a >> 33))) >> 33));
  v21 = v20 ^ (v20 >> 33);
  v18 = 0xFF51AFD7ED558CCDLL * ((h2a + h1a) ^ ((h2a + h1a) >> 33));
  v19 = (0xC4CEB9FE1A85EC53LL * (v18 ^ (v18 >> 33))) ^ ((0xC4CEB9FE1A85EC53LL * (v18 ^ (v18 >> 33))) >> 33);
  *(_QWORD *)out = v21 + v19;
  *((_QWORD *)out + 1) = v19 + v21 + v19;
}