int func0(int n)
{
    int bin=0, i, j, k;
    for(i=0; n!=0; i++)
    {
        j=n%2;
        k=1;
        for(j=0; j<i; j++)
            k=k*10;
        bin=bin+j*k;
        n=n/2;
    }
    return bin;
}