unsigned int sgl_len (unsigned int n)
{
    return ((n-1) * 3 / 2) + ((n-1) & 1) + 2;
}