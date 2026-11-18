double area_of_circle(int radius, int sector)
{
 double pi = 3.14;
 double area;

 if(sector >= 361) {
  area = -1;
 } else {
  area = pi * radius * radius * (sector / 360.0);
 }

 return area;
}