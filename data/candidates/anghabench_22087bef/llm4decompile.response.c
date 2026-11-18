unsigned char
linear2ulaw(
 short pcm_val)
{
 unsigned char uval;

 uval = 0;

 if (pcm_val < 0) {
  pcm_val = -pcm_val;
  uval |= 0x80;
 }

 pcm_val += BIAS;

 uval |= (unsigned char) (0x7F & linear2ulaw::exp_lut[pcm_val >> 7]);
 uval |= (unsigned char) (((pcm_val >> (linear2ulaw::exp_lut[pcm_val >> 7] + 3)) & 0xF) << 4);

 return (uval ^ 0xFF);
}