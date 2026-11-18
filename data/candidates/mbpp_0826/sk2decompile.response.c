char* func0(int a, int b, int c) {
  int a2 = pow((double)a, 2.0);
  int b2 = pow((double)b, 2.0);
  int c2 = pow((double)c, 2.0);
  if (a2 == b2 + c2 || b2 == a2 + c2 || c2 == a2 + b2)
    return "Right-angled Triangle";
  else if (a2 > b2 + c2 || b2 > a2 + c2 || c2 > a2 + b2)
    return "Obtuse-angled Triangle";
  else
    return "Acute-angled Triangle";
}