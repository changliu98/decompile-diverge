char* jstrescapecpy (char* pt, const char* spt)
{



 int i =0, j=0;

 if (!spt) {

  pt[0] = '\0';
  return &pt[0];
 }

 while (spt[i] != '\0') {
  switch (spt[i]) {
   case '\'':
    pt[j++] = '\\';
    pt[j++] = spt[i++];
    break;
   case '\\':
    pt[j++] = '\\';
    pt[j++] = spt[i++];
    break;
   case '%':
    pt[j++] = '_'; i++;
    break;
   default:
    pt[j++] = spt[i++];
  }
 }
 pt[j++] = '\0';
 return &pt[0];
}