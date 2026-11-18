void * mrbc_raw_realloc(void *ptr,uint size)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  MEMORY_POOL *pool_00;
  FREE_BLOCK *pFVar15;
  FREE_BLOCK *pFVar16;
  void *__dest;
  uint uVar17;
  void *new_ptr;
  FREE_BLOCK *release;
  FREE_BLOCK *next;
  uint32_t alloc_size;
  USED_BLOCK *target;
  MEMORY_POOL *pool;
  uint size_local;
  void *ptr_local;
  void *local_10;
  
  pool_00 = memory_pool;
  if ((ptr == (void *)0x0) || (size != 0)) {
    pFVar15 = (FREE_BLOCK *)((long)ptr + -4);
    alloc_size = (-(size + 4) & 3) + size + 4;
    if (alloc_size < 0x20) {
      alloc_size = 0x20;
    }
    uVar17._0_3_ = pFVar15->size;
    uVar17._3_1_ = pFVar15->vm_id;
    if ((uVar17 & 0xfffffc) < alloc_size) {
      uVar1._0_3_ = pFVar15->size;
      uVar1._3_1_ = pFVar15->vm_id;
      pFVar16 = (FREE_BLOCK *)((long)&pFVar15->size + (long)(int)(uVar1 & 0xfffffc));
      uVar2._0_3_ = pFVar16->size;
      uVar2._3_1_ = pFVar16->vm_id;
      if (((uVar2 & 1) != 0) ||
         (uVar3._0_3_ = pFVar15->size, uVar3._3_1_ = pFVar15->vm_id, uVar4._0_3_ = pFVar16->size,
         uVar4._3_1_ = pFVar16->vm_id, (uVar3 & 0xfffffc) + (uVar4 & 0xfffffc) < alloc_size)) {
        __dest = mrbc_raw_alloc(size);
        if (__dest == (void *)0x0) {
          return (void *)0x0;
        }
        uVar13._0_3_ = pFVar15->size;
        uVar13._3_1_ = pFVar15->vm_id;
        memcpy(__dest,ptr,(long)(int)(uVar13 & 0xfffffc) - 4);
        uVar14._0_3_ = pFVar15->size;
        uVar14._3_1_ = pFVar15->vm_id;
        mrbc_set_vm_id(__dest,uVar14 >> 0x18);
        mrbc_raw_free(ptr);
        return __dest;
      }
      remove_free_block(memory_pool,pFVar16);
      merge_block(pFVar15,pFVar16);
    }
    uVar5._0_3_ = pFVar15->size;
    uVar5._3_1_ = pFVar15->vm_id;
    pFVar16 = (FREE_BLOCK *)((long)&pFVar15->size + (long)(int)(uVar5 & 0xfffffc));
    pFVar15 = split_block(pFVar15,alloc_size);
    local_10 = ptr;
    if (pFVar15 == (FREE_BLOCK *)0x0) {
      uVar8._0_3_ = pFVar16->size;
      uVar8._3_1_ = pFVar16->vm_id;
      uVar9._0_3_ = pFVar16->size;
      uVar9._3_1_ = pFVar16->vm_id;
      uVar17 = uVar9 & 0xff000000 | uVar8 & 0xffffff | 2;
      pFVar16->size = (int3)uVar17;
      pFVar16->vm_id = (char)(uVar17 >> 0x18);
    }
    else {
      uVar6._0_3_ = pFVar15->size;
      uVar6._3_1_ = pFVar15->vm_id;
      uVar7._0_3_ = pFVar15->size;
      uVar7._3_1_ = pFVar15->vm_id;
      uVar17 = uVar7 & 0xff000000 | uVar6 & 0xffffff | 2;
      pFVar15->size = (int3)uVar17;
      pFVar15->vm_id = (char)(uVar17 >> 0x18);
      uVar10._0_3_ = pFVar16->size;
      uVar10._3_1_ = pFVar16->vm_id;
      if ((uVar10 & 1) == 0) {
        remove_free_block(pool_00,pFVar16);
        merge_block(pFVar15,pFVar16);
      }
      else {
        uVar11._0_3_ = pFVar16->size;
        uVar11._3_1_ = pFVar16->vm_id;
        uVar12._0_3_ = pFVar16->size;
        uVar12._3_1_ = pFVar16->vm_id;
        uVar17 = uVar12 & 0xff000000 | uVar11 & 0xfffffd;
        pFVar16->size = (int3)uVar17;
        pFVar16->vm_id = (char)(uVar17 >> 0x18);
      }
      add_free_block(pool_00,pFVar15);
    }
  }
  else {
    mrbc_raw_free(ptr);
    local_10 = (void *)0x0;
  }
  return local_10;
}