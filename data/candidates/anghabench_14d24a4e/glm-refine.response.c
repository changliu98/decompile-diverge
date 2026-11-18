unsigned int __cdecl sgl_len(unsigned int n)
{
    if (n == 0)
        return 0;

    unsigned int i = n - 1;
    return (i / 2) + (i % 2) + 2;
}