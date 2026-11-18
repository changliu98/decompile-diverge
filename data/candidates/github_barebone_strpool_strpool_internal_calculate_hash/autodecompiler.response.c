unsigned int strpool_internal_calculate_hash(char *str, int len, int ignore_case)
{
 unsigned int hash = 5381;
 int i;
 char c;

 if (ignore_case) {
  for (i = 0; i < len; i++) {
   c = str[i];
   if (c >= 'a' && c <= 'z')
    c -= 32;
   hash = ((hash << 5) + hash) ^ c;
  }
 } else {
  for (i = 0; i < len; i++) {
   c = str[i];
   hash = ((hash << 5) + hash) ^ c;
  }
 }

 if (hash == 0)
  hash = 1;

 return hash;
}