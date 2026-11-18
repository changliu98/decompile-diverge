int __cdecl prot2perm(int x)
{
    int r = 0;

    if (x & 1)  // PROT_READ
        r = 4;  // S_IRUSR

    if (x & 2)  // PROT_WRITE
        r |= 2; // S_IWUSR

    if (x & 4)  // PROT_EXEC
        r |= 1; // S_IXUSR

    return r;
}