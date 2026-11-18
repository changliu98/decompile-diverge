int toupper(int c)
{
 int upper;
 if ((c >= 'a') && (c <= 'z'))
 {
  upper = c - ('a' - 'A');
 }
 else if ((c >= 0xE0) && (c <= 0xFE) && (c != 0xF7))
 {
  upper = c - ('a' - 'A');
 }
 else
 {
  upper = c;
 }
 return upper;
}