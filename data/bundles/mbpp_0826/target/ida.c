char *__cdecl func0(int a, int b, int c)
{
  int sqc; // [rsp+0h] [rbp-20h]
  int sqb; // [rsp+4h] [rbp-1Ch]
  int sqa; // [rsp+8h] [rbp-18h]

  sqa = (int)pow((double)a, 2.0);
  sqb = (int)pow((double)b, 2.0);
  sqc = (int)pow((double)c, 2.0);
  if ( sqa == sqc + sqb || sqb == sqc + sqa || sqc == sqb + sqa )
    return "Right-angled Triangle";
  if ( sqa <= sqb + sqc && sqb <= sqc + sqa && sqc <= sqb + sqa )
    return "Acute-angled Triangle";
  return "Obtuse-angled Triangle";
}