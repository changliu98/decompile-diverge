void __cdecl subpixels(
        unsigned __int64 p,
        unsigned __int64 *a,
        unsigned __int64 *r,
        unsigned __int64 *g,
        unsigned __int64 *b)
{
  *a = BYTE3(p);
  *r = BYTE2(p);
  *g = BYTE1(p);
  *b = (unsigned __int8)p;
}