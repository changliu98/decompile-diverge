void swap_8 (void * s)
{
    char tmp;
    tmp = *((char *) s + 0);
    *((char *) s + 0) = *((char *) s + 7);
    *((char *) s + 7) = tmp;
    tmp = *((char *) s + 1);
    *((char *) s + 1) = *((char *) s + 6);
    *((char *) s + 6) = tmp;
    tmp = *((char *) s + 2);
    *((char *) s + 2) = *((char *) s + 5);
    *((char *) s + 5) = tmp;
    tmp = *((char *) s + 3);
    *((char *) s + 3) = *((char *) s + 4);
    *((char *) s + 4) = tmp;
}