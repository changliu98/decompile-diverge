int foo(int a, int *b) {
  if (a == 9)
    b[1] = 0;
  else
    b[0] = 0;
  return 3;
}