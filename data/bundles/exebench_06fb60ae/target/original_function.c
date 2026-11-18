static void icvDetMatrix3x3_64d( const double* mat, double* det )
{


    *det = mat[(0)*3 + (0)]*(mat[(1)*3 + (1)]*mat[(2)*3 + (2)] - mat[(1)*3 + (2)]*mat[(2)*3 + (1)]) -
           mat[(0)*3 + (1)]*(mat[(1)*3 + (0)]*mat[(2)*3 + (2)] - mat[(1)*3 + (2)]*mat[(2)*3 + (0)]) +
           mat[(0)*3 + (2)]*(mat[(1)*3 + (0)]*mat[(2)*3 + (1)] - mat[(1)*3 + (1)]*mat[(2)*3 + (0)]);



    ;
}