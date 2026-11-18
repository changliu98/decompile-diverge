void __cdecl MurmurHash3_x86_128(const void *key, const int len, uint32_t seed, void *out)
{
  uint32_t k4_0; // [rsp+8h] [rbp-E8h]
  uint32_t k3_0; // [rsp+Ch] [rbp-E4h]
  uint32_t k2_0; // [rsp+10h] [rbp-E0h]
  uint32_t k1_0; // [rsp+14h] [rbp-DCh]
  const uint8_t *tail; // [rsp+18h] [rbp-D8h]
  const uint32_t *blocks; // [rsp+30h] [rbp-C0h]
  int h4; // [rsp+48h] [rbp-A8h]
  int h4a; // [rsp+48h] [rbp-A8h]
  int h3; // [rsp+4Ch] [rbp-A4h]
  int h3a; // [rsp+4Ch] [rbp-A4h]
  int h2; // [rsp+50h] [rbp-A0h]
  int h2a; // [rsp+50h] [rbp-A0h]
  int h1; // [rsp+54h] [rbp-9Ch]
  uint32_t h1a; // [rsp+54h] [rbp-9Ch]
  uint32_t h1b; // [rsp+54h] [rbp-9Ch]
  int i; // [rsp+58h] [rbp-98h]
  unsigned int v20; // [rsp+8Ch] [rbp-64h]
  unsigned int v21; // [rsp+94h] [rbp-5Ch]
  unsigned int v22; // [rsp+9Ch] [rbp-54h]
  unsigned int v23; // [rsp+A4h] [rbp-4Ch]
  unsigned int v24; // [rsp+ACh] [rbp-44h]
  unsigned int v25; // [rsp+B4h] [rbp-3Ch]
  unsigned int v26; // [rsp+BCh] [rbp-34h]
  unsigned int v27; // [rsp+C4h] [rbp-2Ch]
  unsigned int v28; // [rsp+CCh] [rbp-24h]
  unsigned int v29; // [rsp+D4h] [rbp-1Ch]
  unsigned int v30; // [rsp+DCh] [rbp-14h]
  unsigned int v31; // [rsp+E0h] [rbp-10h]
  unsigned int v32; // [rsp+E0h] [rbp-10h]
  unsigned int v33; // [rsp+E4h] [rbp-Ch]
  unsigned int v34; // [rsp+E4h] [rbp-Ch]
  unsigned int v35; // [rsp+E8h] [rbp-8h]
  unsigned int v36; // [rsp+E8h] [rbp-8h]
  unsigned int v37; // [rsp+ECh] [rbp-4h]

  h1 = seed;
  h2 = seed;
  h3 = seed;
  h4 = seed;
  blocks = (const uint32_t *)((char *)key + 16 * (len / 16));
  for ( i = len / -16; i; ++i )
  {
    v30 = 597399067 * blocks[4 * i];
    v29 = h1 ^ (-1425107063 * ((v30 >> 17) | (v30 << 15)));
    h1 = 5 * (((v29 >> 13) | (v29 << 19)) + h2) + 1444728091;
    v28 = -1425107063 * blocks[4 * i + 1];
    v27 = h2 ^ (951274213 * (HIWORD(v28) | (v28 << 16)));
    h2 = 5 * (((v27 >> 15) | (v27 << 17)) + h3) + 197830471;
    v26 = 951274213 * blocks[4 * i + 2];
    v25 = h3 ^ (-1578923117 * ((v26 >> 15) | (v26 << 17)));
    h3 = 5 * (((v25 >> 17) | (v25 << 15)) + h4) - 1764942795;
    v24 = -1578923117 * blocks[4 * i + 3];
    v23 = h4 ^ (597399067 * ((v24 >> 14) | (v24 << 18)));
    h4 = 5 * (((v23 >> 19) | (v23 << 13)) + h1) + 850148119;
  }
  tail = (const uint8_t *)key + 16 * (len / 16);
  k1_0 = 0;
  k2_0 = 0;
  k3_0 = 0;
  k4_0 = 0;
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
      k4_0 = tail[14] << 16;
LABEL_6:
      k4_0 ^= tail[13] << 8;
LABEL_7:
      v22 = -1578923117 * (k4_0 ^ tail[12]);
      h4 ^= 597399067 * ((v22 >> 14) | (v22 << 18));
LABEL_8:
      k3_0 = tail[11] << 24;
LABEL_9:
      k3_0 ^= tail[10] << 16;
LABEL_10:
      k3_0 ^= tail[9] << 8;
LABEL_11:
      v21 = 951274213 * (k3_0 ^ tail[8]);
      h3 ^= -1578923117 * ((v21 >> 15) | (v21 << 17));
LABEL_12:
      k2_0 = tail[7] << 24;
LABEL_13:
      k2_0 ^= tail[6] << 16;
LABEL_14:
      k2_0 ^= tail[5] << 8;
LABEL_15:
      v20 = -1425107063 * (k2_0 ^ tail[4]);
      h2 ^= 951274213 * (HIWORD(v20) | (v20 << 16));
LABEL_16:
      k1_0 = tail[3] << 24;
LABEL_17:
      k1_0 ^= tail[2] << 16;
LABEL_18:
      k1_0 ^= tail[1] << 8;
LABEL_19:
      h1 ^= -1425107063 * (((597399067 * (k1_0 ^ *tail)) >> 17) | (-888307712 * (k1_0 ^ *tail)));
      break;
    default:
      break;
  }
  h2a = h2 ^ len;
  h3a = h3 ^ len;
  h4a = h4 ^ len;
  h1a = (h1 ^ len) + h2a + h3a + h4a;
  v37 = -1028477387 * ((-2048144789 * (h1a ^ HIWORD(h1a))) ^ ((-2048144789 * (h1a ^ HIWORD(h1a))) >> 13));
  v35 = -2048144789 * ((h2a + h1a) ^ ((h2a + h1a) >> 16));
  v36 = (-1028477387 * (v35 ^ (v35 >> 13))) ^ ((-1028477387 * (v35 ^ (v35 >> 13))) >> 16);
  v33 = -2048144789 * ((h3a + h1a) ^ ((h3a + h1a) >> 16));
  v34 = (-1028477387 * (v33 ^ (v33 >> 13))) ^ ((-1028477387 * (v33 ^ (v33 >> 13))) >> 16);
  v31 = -2048144789 * ((h4a + h1a) ^ ((h4a + h1a) >> 16));
  v32 = (-1028477387 * (v31 ^ (v31 >> 13))) ^ ((-1028477387 * (v31 ^ (v31 >> 13))) >> 16);
  h1b = (v37 ^ HIWORD(v37)) + v36 + v34 + v32;
  *(_DWORD *)out = h1b;
  *((_DWORD *)out + 1) = v36 + h1b;
  *((_DWORD *)out + 2) = v34 + h1b;
  *((_DWORD *)out + 3) = v32 + h1b;
}