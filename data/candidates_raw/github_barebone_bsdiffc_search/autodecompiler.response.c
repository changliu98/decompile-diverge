int main() {
  unsigned char *old,*new;
  long oldsize,newsize;
  long ret;

  readfile( &old, &oldsize, "old" );
  readfile( &new, &newsize, "new" );

  ret = match( old, oldsize, new, newsize );

  printf__bench("%ld\n",ret);

  free__bench(old); free__bench(new);

  return 0;
}