void deblock(short *coef)
{
  int i;
  int a1; int a2; int a3; int a4;
  int b1; int b2; int b3; int b4;
  int c1; int c2; int c3; int c4;
  int d1; int d2; int d3; int d4;
  for (i = 0; i < 4; i++)
  {
    b1 = coef[4 * i + 0];
    c1 = coef[4 * i + 1];
    a1 = b1 + coef[4 * i + 2];
    d1 = coef[4 * i + 3] - c1;
    b2 = (a1 - d1) >> 1 - b1;
    c2 = (a1 - d1) >> 1 - c1;
    coef[4 * i + 0] = a1 - c2;
    coef[4 * i + 1] = c2;
    coef[4 * i + 2] = d1 + b2;
    coef[4 * i + 3] = b2;
  }
  for (i = 0; i < 4; i++)
  {
    b1 = coef[4 * i + 1];
    c1 = coef[4 * i + 2];
    a1 = b1 + coef[4 * i + 0];
    d1 = coef[4 * i + 3] - c1;
    b2 = (a1 - d1) >> 1 - b1;
    c2 = (a1 - d1) >> 1 - c1;
    a2 = a1 - c2;
    b2 = b2 + b2;
    c2 = c2 + c2;
    d2 = d1 + c2;
    a3 = a2 - d2;
    b3 = b2 - d2;
    c3 = c2 - d2;
    d3 = d2 - d2;
    a4 = a3 - d3;
    b4 = b3 - d3;
    c4 = c3 - d3;
    d4 = d3 - d3;
    coef[4 * i + 0] = a4 - c4;
    coef[4 * i + 1] = c4 - d4;
    coef[4 * i + 2] = a4 - d4;
    coef[4 * i + 3] = d4 - d4;
  }
}