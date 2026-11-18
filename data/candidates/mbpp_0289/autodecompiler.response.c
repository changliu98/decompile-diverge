int func0(int year) {
 int hund1 = year / 100;
 int hund4 = year / 400;
 int leap = year >> 2;
 int oodd = year - leap;
 if(hund1) {
  oodd += hund1;
  leap -= hund1;
 }
 if(hund4) {
  oodd -= hund4;
  leap += hund4;
 }
 int days = oodd + (leap << 1);
 int odd = days % 7;
 return odd;
}