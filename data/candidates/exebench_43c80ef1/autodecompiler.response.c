void IndexToData(int *iX, int *iY, int nIndex)
{
 *iY = nIndex & 3;
 *iX = nIndex >> 2;
}