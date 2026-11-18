void merge(int *a, int n, int *b)
{
    int i,j,k,l;
    for(i=0;;i++)
    {
        if(i>=n-1) break;
        j=i+1;
        while(1)
        {
            if(j>=n) break;
            if(a[i]>a[j])
            {
                int temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
            j++;
        }
    }
    l=0;
    k=n-1;
    int m=0;
    while(1)
    {
        if(l>k) break;
        if(l==k)
        {
            b[m++]=a[l++];
        }
        else
        {
            b[m++]=a[l++];
            b[m++]=a[k--];
        }
    }
}