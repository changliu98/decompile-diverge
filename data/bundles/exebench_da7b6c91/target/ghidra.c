void avro_refcount_set(int *refcount,int value)

{
  int value_local;
  int *refcount_local;
  
  *refcount = value;
  return;
}