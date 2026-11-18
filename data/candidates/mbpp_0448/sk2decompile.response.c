int func0(int p0) {
  int l2 = p0;
  int l3 = 3;
  int l4 = 0;
  int l5 = 2;
  int l6;
  int l7;
  if (l2 == 0) return 3;
  if (l2 == 1) return 3;
  if (l2 == 2) return 5;
  l7 = 5;
  while (l2 > 2) {
    l6 = l3 + l4;
    l7 += l6;
    l3 = l4;
    l4 = l5;
    l5 = l6;
    l2--;
  }
  return l7;
}