char *checkfile(char *filename)
{
 int i, len, dot = 0, num = 0;
 char c, *ret;
 len = strlen(filename);
 if(len < 6)
 {
  ret = "No";
 }
 else
 {
  c = filename[0];
  if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
  {
   ret = "No";
  }
  else
  {
   char *ext = &filename[len-4];
   if(strcmp(ext, ".txt") && strcmp(ext, ".exe") && strcmp(ext, ".dll"))
   {
    ret = "No";
   }
   else
   {
    for(i=0;i<len;i++)
    {
     if(filename[i] >= '0' && filename[i] <= '9')
      num++;
     if(filename[i] == '.')
      dot++;
    }
    if(num > 3 || dot != 1)
     ret = "No";
    else
     ret = "Yes";
   }
  }
 }
 return ret;
}