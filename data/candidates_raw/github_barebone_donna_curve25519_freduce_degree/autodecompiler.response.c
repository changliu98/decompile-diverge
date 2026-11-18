static void gf4096x_add_cache( gf4096x* dest )
{
    dest->c0 = dest->c0 + (dest->c1 << 4);
    dest->c0 = dest->c0 + (dest->c1 << 1);
    dest->c0 = dest->c0 + dest->c1;
    dest->c2 = dest->c2 + (dest->c3 << 4);
    dest->c2 = dest->c2 + (dest->c3 << 1);
    dest->c2 = dest->c2 + dest->c3;
    dest->c4 = dest->c4 + (dest->c5 << 4);
    dest->c4 = dest->c4 + (dest->c5 << 1);
    dest->c4 = dest->c4 + dest->c5;
    dest->c6 = dest->c6 + (dest->c7 << 4);
    dest->c6 = dest->c6 + (dest->c7 << 1);
    dest->c6 = dest->c6 + dest->c7;
    dest->c8 = dest->c8 + (dest->c9 << 4);
    dest->c8 = dest->c8 + (dest->c9 << 1);
    dest->c8 = dest->c8 + dest->c9;
    dest->c10 = dest->c10 + (dest->c11 << 4);
    dest->c10 = dest->c10 + (dest->c11 << 1);
    dest->c10 = dest->c10 + dest->c11;
    dest->c12 = dest->c12 + (dest->c13 << 4);
    dest->c12 = dest->c12 + (dest->c13 << 1);
    dest->c12 = dest->c12 + dest->c13;
    dest->c14 = dest->c14 + (dest->c15 << 4);
    dest->c14 = dest->c14 + (dest->c15 << 1);
    dest->c14 = dest->c14 + dest->c15;
    dest->c16 = dest->c16 + (dest->c17 << 4);
    dest->c16 = dest->c16 + (dest->c17 << 1);
    dest->c16 = dest->c16 + dest->c17;
    dest->c18 = dest->c18 + (dest->c19 << 4);
    dest->c18 = dest->c18 + (dest->c19 << 1);
    dest->c18 = dest->c18 + dest->c19;
}