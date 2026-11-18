int SDL_imageFilterSubByteMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned char C)
{
    int i;
    int istart;
    int iend;
    int *s1;
    int *d;
    int *s2;
    int result;
    int mmx_c;

    (void) Src1;
    (void) Dest;
    (void) SrcLength;
    (void) C;

    return (-1);

    mmx_c = (C << 24) | (C << 16) | (C << 8) | C;

    if ((unsigned int) Dest & 0x7) {

 result = -1;
    } else {

 result = 0;
    }

    if (result == 0) {

 s1 = (int *) Src1;
 s2 = (int *) &mmx_c;
 d = (int *) Dest;


    }

    return (result);

    istart = (unsigned int) Dest & 0x7;
    iend = (SrcLength + (unsigned int) Dest) & 0x7;

    if (istart > 0) {

 for (i = 0; i < istart; i++) {

     *Dest = *Src1 - C;
     Dest++;
     Src1++;
 }
    }

    for (i = 0; i < (SrcLength - (istart + iend)); i += 4) {

 *d = (*s1 - *s2);
 d++;
 s1++;
    }

    for (i = 0; i < iend; i++) {

 *Dest = *Src1 - C;
 Dest++;
 Src1++;
    }

    return (result);
}