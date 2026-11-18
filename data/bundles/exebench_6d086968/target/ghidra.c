void mat_copy_vector_l3(long *a,long *b)

{
  long *b_local;
  long *a_local;
  
  *a = *b;
  a[1] = b[1];
  a[2] = b[2];
  return;
}