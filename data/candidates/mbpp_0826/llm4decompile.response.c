char* func0(int a, int b, int c)
{
 int sqa, sqb, sqc;
 sqa = pow(a, 2);
 sqb = pow(b, 2);
 sqc = pow(c, 2);
 char *result;
 if(sqa == (sqb + sqc) || sqb == (sqa + sqc) || sqc == (sqa + sqb))
  result = "Right-angled Triangle";
 else if(sqa > (sqb + sqc) || sqb > (sqa + sqc) || sqc > (sqa + sqb))
  result = "Obtuse-angled Triangle";
 else
  result = "Acute-angled Triangle";
 return result;
}