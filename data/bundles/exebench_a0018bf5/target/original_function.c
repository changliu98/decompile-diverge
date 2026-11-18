inline static void innerdct(const double*a,double*b, const double*c)
{
# 137 "dct.c"
    double b0,b1,b2,b3,b4,b5;
    b2 = (a[0]+a[7]);
    b3 = (a[1]+a[6]);
    b4 = (a[2]+a[5]);
    b5 = (a[3]+a[4]);

    b0 = (b2+b5)*c[4];
    b1 = (b3+b4)*c[4];
    b[0*8] = b0 + b1;
    b[4*8] = b0 - b1;
    b[2*8] = (b2-b5)*c[2] + (b3-b4)*c[6];
    b[6*8] = (b2-b5)*c[6] + (b4-b3)*c[2];

    b0 = (a[0]-a[7]);
    b1 = (a[1]-a[6]);
    b2 = (a[2]-a[5]);
    b3 = (a[3]-a[4]);

    b[1*8] = b0*c[1] + b1*c[3] + b2*c[5] + b3*c[7];
    b[3*8] = b0*c[3] - b1*c[7] - b2*c[1] - b3*c[5];
    b[5*8] = b0*c[5] - b1*c[1] + b2*c[7] + b3*c[3];
    b[7*8] = b0*c[7] - b1*c[5] + b2*c[3] - b3*c[1];
}