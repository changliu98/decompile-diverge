int64_t vcomma(uint8_t *json,int64_t len,int64_t i,uint8_t end)

{
  long lVar1;
  uint uVar2;
  long local_38;
  uint8_t end_local;
  int64_t i_local;
  int64_t len_local;
  uint8_t *json_local;
  long local_10;
  
  if (i == len) {
    local_10 = -(i + 1);
  }
  else {
    lVar1 = i;
    local_10 = i;
    if (json[i] != ',') {
      do {
        i_local = lVar1;
        uVar2 = (uint)json[i_local];
        if (((1 < uVar2 - 9) && (uVar2 != 0xd)) && (uVar2 != 0x20)) {
          if (uVar2 != 0x2c) {
            if (json[i_local] == end) {
              local_38 = i_local;
            }
            else {
              local_38 = -(i_local + 1);
            }
            return local_38;
          }
          return i_local;
        }
        lVar1 = i_local + 1;
      } while (i_local + 1 < len);
      local_10 = -(i_local + 2);
    }
  }
  return local_10;
}