void __cdecl swap_long(long *pi)
{
    unsigned int *p = (unsigned int *)pi;
    *p = ((*p & 0x000000FF) << 24) |
         ((*p & 0x0000FF00) << 8)  |
         ((*p & 0x00FF0000) >> 8)  |
         ((*p & 0xFF000000) >> 24);
}