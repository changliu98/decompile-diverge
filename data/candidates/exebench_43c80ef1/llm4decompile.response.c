void IndexToData(int *iFaceOut, int *iVertOut, int iIndexIn)
{
    *iVertOut = iIndexIn & 3;
    *iFaceOut = iIndexIn >> 2;
}