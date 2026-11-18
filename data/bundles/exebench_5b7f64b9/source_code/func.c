
int dspline( double *x, double *y, int n,
             int if1, double cond1, int ifn, double condn, double *y2 )
{
    int i__1, i__, k;
    double p, u[2000], qn, un, sig;
# 49 "dspline.c"
    --y2;
    --y;
    --x;


    if ( n > 2000 )
    {
        return 1;
    }


    if ( if1 == 2 )
    {



        y2[1] = 0.;
        u[0] = cond1;
    }
    else if ( if1 == 1 )
    {
# 80 "dspline.c"
        y2[1] = -.5;
        u[0] = 3. / ( x[2] - x[1] ) * ( ( y[2] - y[1] ) / ( x[2] - x[1] ) - cond1 );
    }
    else
    {
        return 2;
    }
# 103 "dspline.c"
    i__1 = n - 1;
    for ( i__ = 2; i__ <= i__1; ++i__ )
    {

        sig = ( x[i__] - x[i__ - 1] ) / ( x[i__ + 1] - x[i__ - 1] );


        p = sig * y2[i__ - 1] + 2.;

        y2[i__] = ( sig - 1. ) / p;

        u[i__ - 1] = ( ( ( y[i__ + 1] - y[i__] ) / ( x[i__ + 1] - x[i__] ) - ( y[i__]
                                                                               - y[i__ - 1] ) / ( x[i__] - x[i__ - 1] ) ) * 6. / ( x[i__ + 1] -
                                                                                                                                   x[i__ - 1] ) - sig * u[i__ - 2] ) / p;
    }
    if ( ifn == 2 )
    {


        qn = 0.;
        un = condn;
    }
    else if ( ifn == 1 )
    {
# 137 "dspline.c"
        qn = .5;

        un = 3. / ( x[n] - x[n - 1] ) * ( condn - ( y[n] - y[n - 1] ) / ( x[n]
                                                                          - x[n - 1] ) );
    }
    else
    {
        return 3;
    }



    y2[n] = ( un - qn * u[n - 2] ) / ( qn * y2[n - 1] + 1. );

    for ( k = n - 1; k >= 1; --k )
    {
        y2[k] = y2[k] * y2[k + 1] + u[k - 1];
    }
    return 0;
}
