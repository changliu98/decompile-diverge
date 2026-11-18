void gsdate (int day, int mon, int year, int *serial)
{
# 21 "gsdate.c"
 int i;
 year = year + 100;
 if (mon > 2) {mon = mon - 3;}
         else {mon = mon + 9; year = year - 1;}
 year = year * 1461;
 year = year / 4;
 mon = mon * 153;
 mon = mon + 2;
 mon = mon / 5;
 i = year + mon + day;
 i = i - 36466;
 if (i > 59) i = i - 1;
 *serial = i;
 return;
}