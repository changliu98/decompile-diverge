void __cdecl stack4_push(unsigned __int64 *s, unsigned __int64 e)
{
  *s = e | (16 * *s);
}