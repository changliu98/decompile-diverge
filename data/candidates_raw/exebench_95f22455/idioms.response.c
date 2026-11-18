void camera(float *pos, int resolutionx, int resolutiony)
{
  pos[0] = (pos[0] - (float)(resolutionx>>1)) / (float)(resolutionx>>1);
  pos[1] = ((float)(resolutiony>>1) - pos[1]) / (float)(resolutionx>>1);
  pos[2] = -1.0f;
}