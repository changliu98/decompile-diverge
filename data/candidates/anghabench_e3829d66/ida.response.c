double __cdecl blue_filter(double white, double *buf)
{
  double blue; // [rsp+0h] [rbp-18h]

  *buf = white * 0.0555179 - 0.99886 * *buf;
  buf[1] = white * 0.0750759 - 0.99332 * buf[1];
  buf[2] = white * 0.153852 - 0.969 * buf[2];
  buf[3] = white * 0.3104856 - 0.8665 * buf[3];
  buf[4] = white * 0.5329522 - 0.55 * buf[4];
  buf[5] = white * -0.016898 + 0.7616000000000001 * buf[5];
  blue = white * 0.5362 + *buf + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6];
  buf[6] = 0.115926 * white;
  return 0.11 * blue;
}