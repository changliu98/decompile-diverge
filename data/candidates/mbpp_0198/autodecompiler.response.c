double func0(int length, int width)
{
 double area;

 if(length < 0 || width < 0) {
  area = -1;
 } else {
  area = (sqrt(3.0) * 3.0 / 4.0) * pow((double)length, 2.0) / (4 * width);
 }

 return area;
}