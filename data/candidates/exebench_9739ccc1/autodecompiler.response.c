void set_stimulus(char *mask, char *bits)
{
    for (;;) {
 switch (*bits) {
 case '\0':
     return;
 case '0':
 case '1':
 case '2':
 case '3':
 case '4':
 case '5':
 case '6':
 case '7':
     *mask &= ~(1 << (*bits - '0'));
 }
 bits++;
    }
}