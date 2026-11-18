const char *__cdecl func0(int a, int b, int c)
{
  int sq_a = a * a;
  int sq_b = b * b;
  int sq_c = c * c;

  if (sq_a == sq_b + sq_c || sq_b == sq_a + sq_c || sq_c == sq_a + sq_b)
    return "Right-angled Triangle";
  if (sq_a < sq_b + sq_c && sq_b < sq_a + sq_c && sq_c < sq_a + sq_b)
    return "Acute-angled Triangle";
  return "Obtuse-angled Triangle";
}