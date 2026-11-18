char *to_base_four(char *str)
{
 char cur = '0';
 char last = '0';
 char next;
 int i = -1;
 int nonzero = 0;
 int back = 0;
 while (cur != '\0')
 {
  next = str[i+1];
  str[i-back+1] = '0' + (cur & 1) * 5 + (next - '0') / 2;
  if (str[i-back+1] == '0' && !nonzero)
   back++;
  else
   nonzero = 1;
  last = cur;
  cur = next;
  i++;
 }
 if (i == back)
 {
  str[0] = '0';
  str[1] = '\0';
 }
 else
  str[i-back] = '\0';
 return last;
}