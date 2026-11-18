int func0(int *a,int n,int s)
{
    int i,j,k;
    int sum=0;
    for(i=0;;i++)
    {
        if(i<n/2)
        {
            if(a[i]!=a[n-1-i])
            break;
            else
            sum=sum+a[i]+a[n-1-i];
        }
        else
        if(n%2==1)
        sum=sum+a[n/2];
        {
            if(sum<=s)
            j=1;
            else
            j=0;
        }
    break;
    }
    return j;
}