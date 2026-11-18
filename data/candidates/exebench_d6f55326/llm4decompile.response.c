void swap_long(uint32_t *i)
{
    unsigned char c1, c2, c3, c4;

    c1 = *((unsigned char *) (i) );
    c2 = *((unsigned char *) (i) + 1);
    c3 = *((unsigned char *) (i) + 2);
    c4 = *((unsigned char *) (i) + 3);

    *((unsigned char *) (i) ) = c4;
    *((unsigned char *) (i) + 1) = c3;
    *((unsigned char *) (i) + 2) = c2;
    *((unsigned char *) (i) + 3) = c1;
}