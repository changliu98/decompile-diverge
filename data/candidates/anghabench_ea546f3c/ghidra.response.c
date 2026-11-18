void insert_dle(uchar *dest,uchar *src,int count)

{
  byte bVar1;
  int iVar2;
  uchar *puVar3;
  int count_local;
  uchar *src_local;
  uchar *dest_local;
  
  count_local = count;
  src_local = src;
  puVar3 = dest;
  while (dest_local = puVar3, iVar2 = count_local + -1, count_local != 0) {
    *dest_local = *src_local;
    puVar3 = src_local + 1;
    bVar1 = *src_local;
    count_local = iVar2;
    src_local = puVar3;
    puVar3 = dest_local + 1;
    if ((uint)bVar1 == DLE) {
      dest_local[1] = (uchar)DLE;
      puVar3 = dest_local + 2;
    }
  }
  return;
}