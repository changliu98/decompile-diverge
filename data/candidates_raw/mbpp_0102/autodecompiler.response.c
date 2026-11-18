char *gen_c_name(char *_name, char *buf)
{
 int capitalize_next;
 int i, j;

 for(i = 0, j = 0, capitalize_next = 1;; i++) {
  if(_name[i] == '\0') {
   buf[j] = '\0';
   return buf;
  }
  else if(_name[i] == '_') capitalize_next = 1;
  else if(capitalize_next) {
   buf[j++] = toupper(_name[i]);
   capitalize_next = 0;
  }
  else buf[j++] = _name[i];
 }
}