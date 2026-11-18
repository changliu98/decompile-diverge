void InvSubBytes(unsigned char state[4][4])
{
  int i, j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      state[i][j] = aes_invsbox[state[i][j] / 16][state[i][j] % 16];
}