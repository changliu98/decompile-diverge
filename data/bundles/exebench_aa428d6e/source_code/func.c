
void
ZVdotC32 (
   int n,
   double y0[],
   double y1[],
   double y2[],
   double x0[],
   double x1[],
   double sums[]
) {
double i00, i01, i10, i11, i20, i21,
         r00, r01, r10, r11, r20, r21,
         xi0, xi1, xr0, xr1, yi0, yi1, yi2, yr0, yr1, yr2 ;
int ii, iloc, rloc ;

i00 = i01 = i10 = i11 = i20 = i21
    = r00 = r01 = r10 = r11 = r20 = r21 = 0.0 ;
for ( ii = rloc = 0, iloc = 1 ; ii < n ; ii++, rloc += 2, iloc += 2 ) {
   yr0 = y0[rloc] ; yi0 = y0[iloc] ;
   yr1 = y1[rloc] ; yi1 = y1[iloc] ;
   yr2 = y2[rloc] ; yi2 = y2[iloc] ;
   xr0 = x0[rloc] ; xi0 = x0[iloc] ;
   xr1 = x1[rloc] ; xi1 = x1[iloc] ;
   r00 += yr0*xr0 + yi0*xi0 ; i00 += yr0*xi0 - yi0*xr0 ;
   r01 += yr0*xr1 + yi0*xi1 ; i01 += yr0*xi1 - yi0*xr1 ;
   r10 += yr1*xr0 + yi1*xi0 ; i10 += yr1*xi0 - yi1*xr0 ;
   r11 += yr1*xr1 + yi1*xi1 ; i11 += yr1*xi1 - yi1*xr1 ;
   r20 += yr2*xr0 + yi2*xi0 ; i20 += yr2*xi0 - yi2*xr0 ;
   r21 += yr2*xr1 + yi2*xi1 ; i21 += yr2*xi1 - yi2*xr1 ;
}
sums[ 0] = r00 ; sums[ 1] = i00 ;
sums[ 2] = r01 ; sums[ 3] = i01 ;
sums[ 4] = r10 ; sums[ 5] = i10 ;
sums[ 6] = r11 ; sums[ 7] = i11 ;
sums[ 8] = r20 ; sums[ 9] = i20 ;
sums[10] = r21 ; sums[11] = i21 ;

return ; }
