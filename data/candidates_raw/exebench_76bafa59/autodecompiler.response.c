static void apply_dc_offset(float *buf, float dc_offset)
{
 float f0r = buf[0];
 float f0i = buf[1];

 float t0r = f0r + f0i;
 float t0i = f0r - f0i;

 buf[0] = dc_offset * t0r;
 buf[1] = dc_offset * t0i;
}