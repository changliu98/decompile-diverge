int jrand_(int *n, int *ix, int *iy, int *iz)
{

    int ret_val;


    static double u, x;
# 150 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/ghisvail/nfft/refs/heads/nfft-3.3/3rdparty/cstripack/cstripack.c"
    *ix = *ix * 171 % 30269;
    *iy = *iy * 172 % 30307;
    *iz = *iz * 170 % 30323;
    x = (double) (*ix) / 30269. + (double) (*iy) / 30307. +
     (double) (*iz) / 30323.;
    jrand_.x = x - (int) x;
    jrand_.u = jrand_.x;
    ret_val = (int) ((double) (*n) * jrand_.u + 1.);
    return ret_val;
}