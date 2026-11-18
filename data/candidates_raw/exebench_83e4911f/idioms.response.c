float next(float sig, float *data)
{
  int i;
  float temp;
  data[0] = data[0] + 1.0;
  if (data[1] > data[0])
  {
    i = (int)data[0];
    temp = data[i];
    sig = sig + data[2]*temp;
    temp = data[i-1];
  }
  else
  {
    i = 4;
    data[0] = 4.0;
    temp = data[4];
    sig = sig + data[2]*temp;
    temp = data[(int)data[1]-1];
  }
  data[i] = data[3]*temp + sig;
  return (temp);
}