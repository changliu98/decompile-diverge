int set_filename(char *to_name,char *from_name)

{
  char *from_name_local;
  char *to_name_local;
  
  from_name_local = from_name;
  to_name_local = to_name;
  while( true ) {
    if (*from_name_local == '\0') {
      *to_name_local = '\0';
      return 1;
    }
    if (*from_name_local == '/') break;
    *to_name_local = *from_name_local;
    to_name_local = to_name_local + 1;
    from_name_local = from_name_local + 1;
  }
  *to_name_local = '\0';
  return 2;
}