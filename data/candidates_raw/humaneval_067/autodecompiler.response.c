int get_delta(char *buf, int len)
{
 char buf1[10];
 char buf2[10];
 int i, j, k, flag;
 memset(buf1, 0, sizeof(buf1));
 memset(buf2, 0, sizeof(buf2));

 flag = 0;
 j = 0;
 for(i=0; ; i++) {
  if(buf[i] == '\0') break;

  if(((*___ctype_b_loc ())[(int) ((buf[i]))] & (unsigned short int) 2048)) {
   if(flag == 0) {
    buf1[j++] = buf[i];
   } else {
    buf2[j++] = buf[i];
   }
  } else {
   if(flag == 0 && j > 0) {
    flag = 1;
    j = 0;
   }
  }
 }

 return len - atoi(buf1) - atoi(buf2);
}