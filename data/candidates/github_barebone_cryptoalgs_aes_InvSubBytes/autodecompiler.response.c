void InvSubBytes(unsigned char state[][4])
{
 state[0][0] = (unsigned char)aes_invsbox[state[0][0] >> 4][state[0][0] & 0x0F];
 state[0][1] = (unsigned char)aes_invsbox[state[0][1] >> 4][state[0][1] & 0x0F];
 state[0][2] = (unsigned char)aes_invsbox[state[0][2] >> 4][state[0][2] & 0x0F];
 state[0][3] = (unsigned char)aes_invsbox[state[0][3] >> 4][state[0][3] & 0x0F];
 state[1][0] = (unsigned char)aes_invsbox[state[1][0] >> 4][state[1][0] & 0x0F];
 state[1][1] = (unsigned char)aes_invsbox[state[1][1] >> 4][state[1][1] & 0x0F];
 state[1][2] = (unsigned char)aes_invsbox[state[1][2] >> 4][state[1][2] & 0x0F];
 state[1][3] = (unsigned char)aes_invsbox[state[1][3] >> 4][state[1][3] & 0x0F];
 state[2][0] = (unsigned char)aes_invsbox[state[2][0] >> 4][state[2][0] & 0x0F];
 state[2][1] = (unsigned char)aes_invsbox[state[2][1] >> 4][state[2][1] & 0x0F];
 state[2][2] = (unsigned char)aes_invsbox[state[2][2] >> 4][state[2][2] & 0x0F];
 state[2][3] = (unsigned char)aes_invsbox[state[2][3] >> 4][state[2][3] & 0x0F];
 state[3][0] = (unsigned char)aes_invsbox[state[3][0] >> 4][state[3][0] & 0x0F];
 state[3][1] = (unsigned char)aes_invsbox[state[3][1] >> 4][state[3][1] & 0x0F];
 state[3][2] = (unsigned char)aes_invsbox[state[3][2] >> 4][state[3][2] & 0x0F];
 state[3][3] = (unsigned char)aes_invsbox[state[3][3] >> 4][state[3][3] & 0x0F];
}