void __cdecl InvSubBytes(BYTE (*state)[4])
{
  (*state)[0] = aes_invsbox[16 * ((int)(*state)[0] >> 4) + ((*state)[0] & 0xF)];
  (*state)[1] = aes_invsbox[16 * ((int)(*state)[1] >> 4) + ((*state)[1] & 0xF)];
  (*state)[2] = aes_invsbox[16 * ((int)(*state)[2] >> 4) + ((*state)[2] & 0xF)];
  (*state)[3] = aes_invsbox[16 * ((int)(*state)[3] >> 4) + ((*state)[3] & 0xF)];
  (*state)[4] = aes_invsbox[16 * ((int)(*state)[4] >> 4) + ((*state)[4] & 0xF)];
  (*state)[5] = aes_invsbox[16 * ((int)(*state)[5] >> 4) + ((*state)[5] & 0xF)];
  (*state)[6] = aes_invsbox[16 * ((int)(*state)[6] >> 4) + ((*state)[6] & 0xF)];
  (*state)[7] = aes_invsbox[16 * ((int)(*state)[7] >> 4) + ((*state)[7] & 0xF)];
  (*state)[8] = aes_invsbox[16 * ((int)(*state)[8] >> 4) + ((*state)[8] & 0xF)];
  (*state)[9] = aes_invsbox[16 * ((int)(*state)[9] >> 4) + ((*state)[9] & 0xF)];
  (*state)[10] = aes_invsbox[16 * ((int)(*state)[10] >> 4) + ((*state)[10] & 0xF)];
  (*state)[11] = aes_invsbox[16 * ((int)(*state)[11] >> 4) + ((*state)[11] & 0xF)];
  (*state)[12] = aes_invsbox[16 * ((int)(*state)[12] >> 4) + ((*state)[12] & 0xF)];
  (*state)[13] = aes_invsbox[16 * ((int)(*state)[13] >> 4) + ((*state)[13] & 0xF)];
  (*state)[14] = aes_invsbox[16 * ((int)(*state)[14] >> 4) + ((*state)[14] & 0xF)];
  (*state)[15] = aes_invsbox[16 * ((int)(*state)[15] >> 4) + ((*state)[15] & 0xF)];
}