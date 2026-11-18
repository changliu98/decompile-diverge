int64_t search(int64_t *I,uint8_t *old,int64_t oldsize,uint8_t *new,int64_t newsize,int64_t st,
              int64_t en,int64_t *pos)

{
  int iVar1;
  int64_t iVar2;
  long en_00;
  size_t local_70;
  int64_t y;
  int64_t x;
  int64_t st_local;
  int64_t newsize_local;
  uint8_t *new_local;
  int64_t oldsize_local;
  uint8_t *old_local;
  int64_t *I_local;
  int64_t local_10;
  
  if (en - st < 2) {
    iVar2 = matchlen(old + I[st],oldsize - I[st],new,newsize);
    local_10 = matchlen(old + I[en],oldsize - I[en],new,newsize);
    if (local_10 < iVar2) {
      *pos = I[st];
      local_10 = iVar2;
    }
    else {
      *pos = I[en];
    }
  }
  else {
    en_00 = st + (en - st) / 2;
    local_70 = newsize;
    if (oldsize - I[en_00] < newsize) {
      local_70 = oldsize - I[en_00];
    }
    iVar1 = memcmp(old + I[en_00],new,local_70);
    if (iVar1 < 0) {
      local_10 = search(I,old,oldsize,new,newsize,en_00,en,pos);
    }
    else {
      local_10 = search(I,old,oldsize,new,newsize,st,en_00,pos);
    }
  }
  return local_10;
}