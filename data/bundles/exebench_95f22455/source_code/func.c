
void convertscreenvertex(float vec[3],int resolutionx,int resolutiony)
  {
  vec[0]=(vec[0]-(float)(resolutionx>>1))/(float)(resolutionx>>1);
  vec[1]=((float)(resolutiony>>1)-vec[1])/(float)(resolutionx>>1);
  vec[2]=-1.0f;
  }
