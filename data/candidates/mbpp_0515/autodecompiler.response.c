int func0(int *a, int n, int k)
{
    if(n>k) return 1;
    char b[k];
    int i,j;
    for(i=0;i<k;++i)
        b[i]=0;
    for(i=0;i<n;++i)
    {
        if(b[0])
        {
            return 1;
        }
        char c[k];
        for(j=0;j<k;++j)
            c[j]=0;
        for(j=0;j<k;++j)
        {
            if(b[j])
            {
                if(!b[(j+a[i])%k])
                    c[(j+a[i])%k]=1;
            }
        }
        for(j=0;j<k;++j)
            if(c[j])
                b[j]=1;
        b[a[i]%k]=1;
    }
    return b[0]&1;
}