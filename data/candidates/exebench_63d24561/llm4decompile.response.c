int zmlt_(doublecomplex *z1, doublecomplex *z2, doublecomplex *zr)
{

    doublecomplex z1_local, z2_local;
    doublecomplex zr_local;


    z1_local = *z1;
    z2_local = *z2;


    zr_local.r = z1_local.r * z2_local.r - z1_local.i * z2_local.i;
    zr_local.i = z1_local.r * z2_local.i + z1_local.i * z2_local.r;


    *zr = zr_local;

    return 0;
}