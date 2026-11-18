char *displayBool(int b, int yesno)
{
 char *s;
 if(b == yesno)
 {
  s = "Y";
 }
 else
 {
  s = "N";
 }
 return s;
}