void nexper(int n, int *a, int *mtc, int *even)
{
    int i,j,l,s,d,m,nm3,ia,j1,j2;

    if (*mtc == 0) {
        for (i=1; i<=n; i++) a[i]=i;
        *mtc=1;
        *even=1;
    } else if (*even == 1) {
        i=a[1];
        a[1]=a[2];
        a[2]=i;
        *even=0;
        if (a[n] == 1 && a[1] == 2+(n%2)) {
            for (i=1; i<=n-3; i++) {
                if (a[i+1] != a[i]+1) return;
            }
            *mtc=0;
        }
    } else {
        s=0;
        for (i=2; i<=n; i++) {
            ia=a[i];
            nm3=i-1;
            d=0;
            for (j=1; j<=nm3; j++) {
                if (ia < a[j]) d++;
            }
            s+=d;
            if (d != (nm3*(s%2))) {
                m=(n+1)*((s+1)%2);
                for (j=1; j<=nm3; j++) {
                    if ((a[j]-ia >= 0 && a[j]-m < 0) || (a[j]-ia < 0 && a[j]-m >= 0)) {
                        m=a[j];
                        l=j;
                    }
                }
                a[l]=ia;
                a[i]=m;
                *even=1;
                return;
            }
        }
        *mtc=0;
    }
}