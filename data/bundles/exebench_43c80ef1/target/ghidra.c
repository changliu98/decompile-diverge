void IndexToData(int *piFace,int *piVert,int iIndexIn)

{
  int iIndexIn_local;
  int *piVert_local;
  int *piFace_local;
  
  *piVert = iIndexIn & 3;
  *piFace = iIndexIn >> 2;
  return;
}