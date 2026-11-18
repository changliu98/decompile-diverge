void SHUF(unsigned char *in, unsigned char *out)
{
   out[0] = in[8];
   out[1] = in[11];
   out[2] = in[12];
   out[3] = in[15];
   out[4] = in[2];
   out[5] = in[1];
   out[6] = in[6];
   out[7] = in[5];
   out[8] = in[10];
   out[9] = in[9];
   out[10] = in[14];
   out[11] = in[13];
   out[12] = in[0];
   out[13] = in[7];
   out[14] = in[4];
   out[15] = in[3];
}