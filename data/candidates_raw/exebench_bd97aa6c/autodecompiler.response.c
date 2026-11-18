void hex_to_rgb(unsigned long int hex, unsigned long int *r, unsigned long int *g, unsigned long int *b)
{
    *r = (hex >> 24) & 0xff;
    *g = (hex >> 16) & 0xff;
    *b = (hex >> 8) & 0xff;
}