void cftb040(float *data)
{
  float a0r = data[0]+data[4];
  float a0i = data[1]+data[5];
  float a1r = data[0]-data[4];
  float a1i = data[1]-data[5];
  float a2r = data[2]+data[6];
  float a2i = data[3]+data[7];
  float a3r = data[2]-data[6];
  float a3i = data[3]-data[7];
  data[0]=a0r+a2r;
  data[1]=a0i+a2i;
  data[2]=a1r+a3i;
  data[3]=a1i-a3r;
  data[4]=a0r-a2r;
  data[5]=a0i-a2i;
  data[6]=a1r-a3i;
  data[7]=a1i+a3r;
}