int func0(char *S)
{
 int i, sum, isi, isstart;

 sum = 0;
 isi = 0;
 isstart = 1;
 for (i = 0; S[i] != '\0'; i++) {
  if ((*__ctype_b_loc ())[(int) ((S[i]))] & (0x2000) && isi) {
   sum++;
   isi = 0;
  }
  if (S[i] == 'I' && isstart)
   isi = 1;
  else if (!((*__ctype_b_loc ())[(int) ((S[i]))] & (0x2000)))
   isi = 0;
  if (!((*__ctype_b_loc ())[(int) ((S[i]))] & (0x2000)))
   isstart = 0;
  if (S[i] == '.' || S[i] == '?' || S[i] == '!')
   isstart = 1;
 }
 return sum;
}