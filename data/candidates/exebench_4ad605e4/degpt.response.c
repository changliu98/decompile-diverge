int atmc_fetch_and_add(uint *address,int value)

{
  uint uVar1;
  int prev;
  int value_local;
  uint *address_local;
  
  LOCK();
  uVar1 = *address;
  *address = *address + value;
  UNLOCK();
  return value + uVar1;
}