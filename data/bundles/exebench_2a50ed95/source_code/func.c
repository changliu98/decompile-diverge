
void
ZVdotC21 (
   int n,
   double y0[],
   double y1[],
   double x0[],
   double sums[]
) {
double i00, i10, r00, r10, xi0, xr0, yi0, yi1, yr0, yr1 ;
int ii, iloc, rloc ;

i00 = i10 = r00 = r10 = 0.0 ;
for ( ii = rloc = 0, iloc = 1 ; ii < n ; ii++, rloc += 2, iloc += 2 ) {
   yr0 = y0[rloc] ; yi0 = y0[iloc] ;
   yr1 = y1[rloc] ; yi1 = y1[iloc] ;
   xr0 = x0[rloc] ; xi0 = x0[iloc] ;
   r00 += yr0*xr0 + yi0*xi0 ; i00 += yr0*xi0 - yi0*xr0 ;
   r10 += yr1*xr0 + yi1*xi0 ; i10 += yr1*xi0 - yi1*xr0 ;
}
sums[ 0] = r00 ; sums[ 1] = i00 ;
sums[ 2] = r10 ; sums[ 3] = i10 ;

return ; }
