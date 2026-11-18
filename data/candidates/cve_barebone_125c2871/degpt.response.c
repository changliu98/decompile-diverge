/* WARNING: Heritage AFTER dead removal. Example location: s0xffffffffffffffc8 : 0x00101ea3 */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

int ff_amf_get_field_value(uint8_t *data,uint8_t *data_end,uint8_t *name,uint8_t *dst,int dst_size)

{
  uint8_t uVar1;
  uint uVar2;
  int iVar3;
  size_t sVar4;
  byte *pbVar5;
  char *pcVar6;
  uint8_t *src;
  int local_7c;
  int size;
  int len;
  int namelen;
  int dst_size_local;
  uint8_t *dst_local;
  uint8_t *name_local;
  uint8_t *data_end_local;
  uint8_t *data_local;
  uint8_t **local_28;
  uint8_t **local_20;
  av_intfloat64 v;
  av_intfloat64 local_10;
  
  data_local = data;
  sVar4 = strlen((char *)name);
  for (; *data_local != '\x03' && data_local < data_end; data_local = data_local + len) {
    len = ff_amf_tag_size(data_local,data_end);
    if (len < 0) {
      len = (int)data_end - (int)data_local;
    }
  }
  if (2 < (long)data_end - (long)data_local) {
    data_local = data_local + 1;
    while( true ) {
      local_20 = &data_local;
      uVar2 = (uint)CONCAT11(*data_local,data_local[1]);
      if (uVar2 == 0) break;
      if ((long)data_end - (long)(data_local + 2) <= (long)(int)uVar2) {
        return -1;
      }
      data_local = data_local + 2 + (int)uVar2;
      if ((uVar2 == (uint)sVar4) &&
         (iVar3 = memcmp(data_local + -(long)(int)uVar2,name,(long)(int)(uint)sVar4), iVar3 == 0)) {
        pbVar5 = data_local + 1;
        uVar1 = *data_local;
        if (uVar1 == '\0') {
          v.i = (ulong)*pbVar5 << 0x38 | (ulong)data_local[2] << 0x30 | (ulong)data_local[3] << 0x28
                | (ulong)data_local[4] << 0x20 | (ulong)data_local[5] << 0x18 |
                (ulong)data_local[6] << 0x10 | (ulong)data_local[7] << 8 | (ulong)data_local[8];
          data_local = pbVar5;
          local_10.i = v.i;
          snprintf((char *)dst,(long)dst_size,"%g",v.i);
        }
        else if (uVar1 == '\x01') {
          pcVar6 = "false";
          if (*pbVar5 != 0) {
            pcVar6 = "true";
          }
          data_local = pbVar5;
          snprintf((char *)dst,(long)dst_size,"%s",pcVar6);
        }
        else {
          if (uVar1 != '\x02') {
            return -1;
          }
          local_28 = &data_local;
          src = data_local + 3;
          local_7c = dst_size;
          if ((int)(CONCAT11(data_local[1],data_local[2]) + 1) <= dst_size) {
            local_7c = CONCAT11(data_local[1],data_local[2]) + 1;
          }
          data_local = src;
          av_strlcpy((char *)dst,(char *)src,(long)local_7c);
        }
        return 0;
      }
      iVar3 = ff_amf_tag_size(data_local,data_end);
      if ((iVar3 < 0) || ((long)data_end - (long)data_local <= (long)iVar3)) {
        return -1;
      }
      data_local = data_local + iVar3;
    }
  }
  return -1;
}