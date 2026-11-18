void __cdecl stack4_replace_top(unsigned __int64 *s, unsigned __int64 e)
{
  *s = (*s & 0xFFFFFFFFFFFFFFF0ULL) | e;
}