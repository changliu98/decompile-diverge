void SubBytes(unsigned char state[4][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            state[i][j] = aes_sbox[(state[i][j] >> 4)][(state[i][j] & 0x0f)];
}