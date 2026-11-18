void bn_sqr_comba4(unsigned long *r, unsigned long *a)
 {
 unsigned long t[8],u,c[4];

 u=(unsigned long)a[0];
 r[0]=u*u;
 u=(unsigned long)a[1];
 r[1]=u*u;
 u=(unsigned long)a[2];
 r[2]=u*u;
 u=(unsigned long)a[3];
 r[3]=u*u;

 u=(unsigned long)a[0];
 t[0]=u*a[1];
 u=(unsigned long)a[0];
 t[1]=u*a[2];
 u=(unsigned long)a[0];
 t[2]=u*a[3];
 u=(unsigned long)a[1];
 t[3]=u*a[2];
 u=(unsigned long)a[1];
 t[4]=u*a[3];
 u=(unsigned long)a[2];
 t[5]=u*a[3];

 c[0]=0;
 c[1]=0;
 c[2]=0;
 c[3]=0;

 u=r[0];
 r[0]=(u&0xffffffffL)+(c[0]<<32);
 c[0]=(u>>32)+c[0];
 u=r[1];
 r[1]=(u&0xffffffffL)+(c[0]<<32);
 c[0]=(u>>32)+c[0];
 u=r[2];
 r[2]=(u&0xffffffffL)+(c[0]<<32);
 c[0]=(u>>32)+c[0];
 u=r[3];
 r[3]=(u&0xffffffffL)+(c[0]<<32);
 c[0]=(u>>32)+c[0];

 u=t[0];
 r[1]+=(u&0xffffffffL)+(c[1]<<32);
 c[1]=(u>>32)+c[1];
 u=t[1];
 r[2]+=(u&0