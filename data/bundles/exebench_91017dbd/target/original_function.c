void ddelete_c(char *path,int *iostat)



{
  *iostat = ( unlink(path) ? errno : 0 );
}