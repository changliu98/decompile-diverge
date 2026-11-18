void nexper(int n, int a[], int *mtc, int *even)


{ int s,d,i,j,nm3,j1,j2,ia,l,i1,m;
  if(*mtc==0)
  { nm3=n-3; for(i=1;i<=n;i++) a[i]=i;
     *mtc=1; *even=1; return;
  }
  if(*even == 1)
  { ia=a[1]; a[1]=a[2]; a[2]=ia; *even=0;
     if(a[n] != 1 || a[1] != 2+(n%2)) return;
     if(n<=3) {*mtc=0; return;}
     for(i=1;i<=n-3;i++)
     { if(a[i+1] != a[i]+1) return; }
     *mtc=0; return;
  }
  else
  { s=0;
     for(i1=2;i1<=n;i1++)
     { ia=a[i1]; i=i1-1;
       for(j=1,d=0;j<=i;j++) { if(a[j] > ia) d++;}
       s+=d;
       if(d != i*(s%2)) goto A;
     }
     *mtc=0; return;
  A: m=((s+1)%2)*(n+1);
     for(j=1;j<=i;j++)
     { j1=a[j]-ia; j2=a[j]-m;
       if((j1 >= 0 && j2 < 0) || (j1<0 && j2>=0) )
       { m=a[j]; l=j;}
     }
     a[l]=ia; a[i1]=m; *even=1; return;
  }
}