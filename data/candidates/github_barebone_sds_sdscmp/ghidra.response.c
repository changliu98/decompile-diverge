int sdscmp(sds s1,sds s2)

{
  size_t sVar1;
  size_t sVar2;
  int local_4c;
  size_t local_48;
  int cmp;
  size_t minlen;
  size_t l2;
  size_t l1;
  sds s2_local;
  sds s1_local;
  int local_c;
  
  sVar1 = sdslen(s1);
  sVar2 = sdslen(s2);
  local_48 = sVar2;
  if (sVar1 < sVar2) {
    local_48 = sVar1;
  }
  local_c = memcmp(s1,s2,local_48);
  if (local_c == 0) {
    if (sVar2 < sVar1) {
      local_4c = 1;
    }
    else {
      local_4c = 0;
      if (sVar1 < sVar2) {
        local_4c = -1;
      }
    }
    local_c = local_4c;
  }
  return local_c;
}