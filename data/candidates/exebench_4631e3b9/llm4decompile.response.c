int c_decrypt(char *cipher)
{
 int i;
 int plain;

 for(i = 0; cipher[i] != '\0'; i++)
 {
  plain = cipher[i] - 13;
  if(plain <= 0)
  {
   plain = 256 + plain;
  }
  cipher[i] = plain % 256;
 }
 return 0;
}