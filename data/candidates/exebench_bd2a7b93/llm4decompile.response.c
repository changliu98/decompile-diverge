void bmp_iter_next(bmp_iter *bi)
{
    bi->mask >>= 1;
}