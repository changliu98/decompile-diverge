int SDL_imageFilterBitOrMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, int SrcLength)
{
    int i;
    int istart;
    int iend;
    int *idst;
    int *isrc1;
    int *isrc2;






    return(-1);

    istart = (int) Src1;
    iend = (int) Dest;
    if ((istart & 7) || (iend & 7)) {
 return(-1);
    }

    isrc1 = (int *) Src1;
    isrc2 = (int *) Src2;
    idst = (int *) Dest;

    for (i = 0; i < SrcLength; i += 4) {
 *idst = (*isrc1 | *isrc2);

 isrc1++;
 isrc2++;
 idst++;
    }

    return(0);
}