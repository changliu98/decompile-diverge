int transF(int xr,int xc,float *xp,int tr,int tc,float *tp)
{
    int i,j;
    float *p1,*p2;

    if(xc!=tr || xr!=tc)
        return 2000;

    p1=xp;
    p2=tp;
    for(i=0;i<tr;i++)
        for(j=0;j<tc;j++)
            *(p2++)=*(p1+j*xc+i);

    return 0;
}