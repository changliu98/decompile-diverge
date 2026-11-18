int gf2_create_table(unsigned char *table, unsigned int prim_poly)
{
    int i;
    unsigned short x;
    if ((prim_poly & 0x100) == 0)
        return -1;
    table[0] = 0;
    table[1] = 1;
    x = 1;
    for (i = 2; i < 256; i++)
    {
        x = (x << 1);
        if (x & 0x100)
            x = x ^ prim_poly;
        table[i] = x;
    }
    return 0;
}