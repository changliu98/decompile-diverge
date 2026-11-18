void __cdecl subpixels(
        unsigned __int64 p,
        unsigned __int64 *a,
        unsigned __int64 *r,
        unsigned __int64 *g,
        unsigned __int64 *b)
{
  *a = (p >> 24) & 0xFF;
  *r = (p >> 16) & 0xFF;
  *g = (p >> 8)  & 0xFF;
  *b =  p        & 0xFF;
}