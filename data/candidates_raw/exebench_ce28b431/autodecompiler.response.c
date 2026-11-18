void swap4( void *s )
{
    char tmp;
    char *c = (char *) s;

    tmp = c[0];
    c[0] = c[3];
    c[3] = tmp;

    tmp = c[1];
    c[1] = c[2];
    c[2] = tmp;
}