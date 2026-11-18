static inline void subpixels(unsigned long p, unsigned long* a,
        unsigned long* r, unsigned long* g, unsigned long* b)
{
  *a = (p >> 24) & 255;
  *r = (p >> 16) & 255;
  *g = (p >> 8) & 255;
  *b = (p >> 0) & 255;
}