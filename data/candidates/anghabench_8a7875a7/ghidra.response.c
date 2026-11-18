char hex_char(uchar val)

{
  uchar val_local;
  undefined1 local_9;
  
  if (val < 10) {
    local_9 = val + '0';
  }
  else if (val < 0x10) {
    local_9 = val + 'W';
  }
  else {
    local_9 = '?';
  }
  return local_9;
}