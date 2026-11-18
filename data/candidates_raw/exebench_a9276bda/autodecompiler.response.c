char * int_to_str(char * s, unsigned int i) {
 int pos;
 s[9] = '\0';
 for (pos = 8; pos >= 0; pos--) {
  s[pos] = (i % 10) + '0';
  i /= 10;
  if (i == 0)
   break;
 }
 return &s[pos];
}