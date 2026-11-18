
static inline void zywrleCalcSize(int* pW, int* pH, int level)
{
 *pW &= ~((1<<level)-1);
 *pH &= ~((1<<level)-1);
}
