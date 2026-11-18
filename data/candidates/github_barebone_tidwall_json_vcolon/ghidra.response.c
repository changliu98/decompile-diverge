int64_t vcolon(uint8_t *json,int64_t len,int64_t i)

{
  long lVar1;
  uint uVar2;
  int64_t i_local;
  int64_t len_local;
  uint8_t *json_local;
  long local_10;
  
  if (i == len) {
    local_10 = -(i + 1);
  }
  else {
    lVar1 = i;
    if (json[i] == ':') {
      local_10 = i + 1;
    }
    else {
      do {
        i_local = lVar1;
        uVar2 = (uint)json[i_local];
        if (((1 < uVar2 - 9) && (uVar2 != 0xd)) && (uVar2 != 0x20)) {
          if (uVar2 != 0x3a) {
            return -(i_local + 1);
          }
          return i_local + 1;
        }
        lVar1 = i_local + 1;
      } while (i_local + 1 < len);
      local_10 = -(i_local + 2);
    }
  }
  return local_10;
}