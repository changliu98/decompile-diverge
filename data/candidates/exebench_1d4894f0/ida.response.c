void __cdecl stack4_replace_top(unsigned __int64 *s, unsigned __int64 e)
{
  *s = e | *s & 0xFFFFFFFFFFFFFFF0LL;
}