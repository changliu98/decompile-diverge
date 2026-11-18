void bmp_iter_next(bmp_t *bmp, int *bit_no)
{
    *bmp >>= 1;
    *bit_no += 1;
}