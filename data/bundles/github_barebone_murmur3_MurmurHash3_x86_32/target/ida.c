void __cdecl MurmurHash3_x86_32(const void *key, int len, uint32_t seed, void *out)
{
  int v4; // [rsp+0h] [rbp-78h]
  uint32_t k1_0; // [rsp+4h] [rbp-74h]
  const uint8_t *tail; // [rsp+8h] [rbp-70h]
  int i; // [rsp+30h] [rbp-48h]
  uint32_t v9; // [rsp+68h] [rbp-10h]
  unsigned int v10; // [rsp+70h] [rbp-8h]
  uint32_t v11; // [rsp+74h] [rbp-4h]

  for ( i = len / -4; i; ++i )
  {
    v10 = -862048943 * *((_DWORD *)key + len / 4 + i);
    v9 = seed ^ (461845907 * ((v10 >> 17) | (v10 << 15)));
    seed = 5 * ((v9 >> 19) | (v9 << 13)) - 430675100;
  }
  tail = (const uint8_t *)key + 4 * (len / 4);
  k1_0 = 0;
  v4 = len & 3;
  switch ( v4 )
  {
    case 1:
      goto LABEL_9;
    case 2:
LABEL_8:
      k1_0 ^= tail[1] << 8;
LABEL_9:
      seed ^= 461845907 * (((-862048943 * (k1_0 ^ *tail)) >> 17) | (380141568 * (k1_0 ^ *tail)));
      break;
    case 3:
      k1_0 = tail[2] << 16;
      goto LABEL_8;
  }
  v11 = -2048144789 * (seed ^ len ^ ((seed ^ len) >> 16));
  *(_DWORD *)out = (-1028477387 * (v11 ^ (v11 >> 13))) ^ ((-1028477387 * (v11 ^ (v11 >> 13))) >> 16);
}