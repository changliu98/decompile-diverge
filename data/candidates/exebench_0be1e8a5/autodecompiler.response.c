void short_to_string(char *dest, unsigned short value)
{
   unsigned char tmp;
   unsigned short base;

   base = 0;
   tmp = (value - base) / 10000; base += tmp * 10000; *dest++ = tmp + '0';
   tmp = (value - base) / 1000; base += tmp * 1000; *dest++ = tmp + '0';
   tmp = (value - base) / 100; base += tmp * 100; *dest++ = tmp + '0';
   tmp = (value - base) / 10; base += tmp * 10; *dest++ = tmp + '0';
   tmp = (value - base); base += tmp; *dest++ = tmp + '0';

   *dest++ = '\0';
}