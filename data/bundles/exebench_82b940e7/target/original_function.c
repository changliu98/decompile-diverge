static inline void clamp(int *a, int *b, const int max)
{
 *b += *a / max;
 *a %= max;
}