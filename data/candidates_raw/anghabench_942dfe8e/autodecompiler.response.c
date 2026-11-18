static int
get_bcd_year(int year)
{
 int ret = 0;

 if ((year & 1) != 0)
  ret |= 4;
 if ((year & 2) != 0)
  ret |= 2;
 if ((year & 4) != 0)
  ret |= 1;

 return ret;
}