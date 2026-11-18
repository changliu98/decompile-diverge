void __cdecl IndexToData(int *piFace, int *piVert, const int iIndexIn)
{
  *piVert = iIndexIn & 3;
  *piFace = iIndexIn >> 2;
}