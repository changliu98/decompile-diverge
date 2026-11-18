void put_user_long(unsigned_long val,int *addr)

{
  int *addr_local;
  unsigned_long val_local;
  
  *addr = (int)val;
  return;
}