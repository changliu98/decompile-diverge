static void IndexToData(int * piFace, int * piVert, const int iIndexIn)
{
 piVert[0] = iIndexIn&0x3;
 piFace[0] = iIndexIn>>2;
}