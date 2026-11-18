void crc16_b(uint *crc,uchar db)

{
  int i;
  uchar db_local;
  uint *crc_local;
  
  db_local = db;
  for (i = 0; i < 8; i = i + 1) {
    *crc = *crc << 1;
    if ((((uint)db_local ^ *crc >> 0x10) & 1) != 0) {
      *crc = *crc ^ 0x8005;
    }
    db_local = (uchar)((int)(uint)db_local >> 1);
  }
  *crc = *crc & 0xffff;
  return;
}