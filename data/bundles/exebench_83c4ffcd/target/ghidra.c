char * copy_line(char *where,char *what,int n)

{
  bool bVar1;
  int i;
  char *now;
  int n_local;
  char *what_local;
  char *where_local;
  
  i = 0;
  now = what;
  where_local = where;
  while( true ) {
    bVar1 = false;
    if (((i < n + -1) && (bVar1 = false, *now != '\0')) && (bVar1 = false, *now != '\n')) {
      bVar1 = *now != '\r';
    }
    if (!bVar1) break;
    *where_local = *now;
    i = i + 1;
    now = now + 1;
    where_local = where_local + 1;
  }
  *where_local = '\0';
  if (*now == '\r') {
    now = now + 1;
  }
  if (*now == '\n') {
    now = now + 1;
  }
  return now;
}