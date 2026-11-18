void swap(int a[])
{
    int minn=0,min,i;
    min=a[0];
    for(i=0; i<10; i++) {
        if(a[i]<min){
            minn=i;
        }
    }
    int maxn=0,max;
    max=a[0];
    for(i=0; i<10; i++) {
        if(a[i]>max){
            maxn=i;
        }
    }
    a[0]=a[0]+a[minn];
    a[minn]=a[0]-a[minn];
    a[0]=a[0]-a[minn];
    a[9]=a[9]+a[maxn];
    a[maxn]=a[9]-a[maxn];
    a[9]=a[9]-a[maxn];


}