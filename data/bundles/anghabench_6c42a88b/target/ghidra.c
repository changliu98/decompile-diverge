size_t ext4_acl_size(int count)

{
  int count_local;
  undefined8 local_10;
  
  if (count < 5) {
    local_10 = (long)count * 4 + 4;
  }
  else {
    local_10 = (long)(count + -4) * 4 + 0x14;
  }
  return local_10;
}