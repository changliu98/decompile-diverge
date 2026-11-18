void SHUF(unsigned char *state, unsigned char *ct)
{
 ct[0] = state[8];
 ct[1] = state[11];
 ct[2] = state[12];
 ct[3] = state[15];
 ct[4] = state[2];
 ct[5] = state[1];
 ct[6] = state[6];
 ct[7] = state[5];
 ct[8] = state[10];
 ct[9] = state[9];
 ct[10] = state[14];
 ct[11] = state[13];
 ct[12] = state[0];
 ct[13] = state[7];
 ct[14] = state[4];
 ct[15] = state[3];
}