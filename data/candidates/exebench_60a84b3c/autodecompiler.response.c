int sraClipRect2(int *x1, int *y1, int *x2, int *y2, int x, int y, int h, int w)
{
 char ret = 0;

 if (*x1 < x) *x1 = x;
 if (*y1 < y) *y1 = y;
 if (*x1 >= x2) *x1 = x2 - 1;
 if (*y1 >= y2) *y1 = y2 - 1;

 if (*x2 <= x) *x2 = x + 1;
 if (*y2 <= y) *y2 = y + 1;
 if (*x2 > x2) *x2 = x2;
 if (*y2 > y2) *y2 = y2;

 if ((*x2 > *x1) && (*y2 > *y1)) ret = 1;

 return ret;
}