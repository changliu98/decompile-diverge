void i2fv(int *piFace, int *piVert, int iIndexIn)
{
  *piVert = iIndexIn & 0x3;
  *piFace = iIndexIn >> 2;
}