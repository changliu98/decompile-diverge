char* func0(int a, int b, int c) {
  int sqa = pow(a, 2);
  int sqb = pow(b, 2);
  int sqc = pow(c, 2);
  if (sqa == sqb + sqc || sqb == sqa + sqc || sqc == sqa + sqb) {
    return "Right-angled Triangle";
  } else if (sqa > sqc + sqb || sqb > sqa + sqc || sqc > sqa + sqb) {
    return "Obtuse-angled Triangle";
  } else {
    return "Acute-angled Triangle";
  }
}