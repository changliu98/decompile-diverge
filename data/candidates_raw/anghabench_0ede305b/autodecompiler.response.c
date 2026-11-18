static unsigned int fons__decutf8(unsigned int* state, unsigned int* codep, unsigned int byte)
{
 int type = fons__decutf8_utf8d[byte];

 unsigned int code = (*state != FONS_UTF8_ACCEPT) ?
  (byte & 0x3fu) | (*codep << 6) :
  (0xff >> type) & byte;

 *codep = code;

 *state = fons__decutf8_utf8d[256 + *state + type];

 return *state;
}