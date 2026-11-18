double func0(int r, int a)
{
 double sectorarea;
 if (a < 360)
  sectorarea = (3.14 * r * r) * (a / 360.0);
 else
  sectorarea = 3.14 * r * r;

 return sectorarea;
}