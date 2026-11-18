void crc8_byte(uint *crc,uchar db)

{
  uint uVar1;
  uint uVar2;
  int f;
  int i;
  uchar db_local;
  uint *crc_local;
  
  db_local = db;
  for (i = 0; i < 8; i = i + 1) {
    uVar1 = *crc;
    uVar2 = (uint)db_local;
    *crc = *crc >> 1;
    db_local = (uchar)((int)(uint)db_local >> 1);
    if (((uVar1 ^ uVar2) & 1) != 0) {
      *crc = *crc ^ 0x8c;
    }
  }
  *crc = *crc & 0xff;
  return;
}