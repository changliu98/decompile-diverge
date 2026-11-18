int rdb_encode_int(long value, char *enc)
{
  if (value >= -128 && value <= 127) {
    enc[0] = (RDB_ENC_INT8 | (RDB_ENCVAL << 6));
    enc[1] = (char)value;
    return 2;
  }
  if (value >= -32768 && value <= 32767) {
    enc[0] = (RDB_ENC_INT16 | (RDB_ENCVAL << 6));
    ((char *)enc)[1] = (value & 0xff);
    ((char *)enc)[2] = (value >> 8) & 0xff;
    return 3;
  }
  if (value >= -0x80000000 && value <= 0x7fffffff) {
    enc[0] = (RDB_ENC_INT32 | (RDB_ENCVAL << 6));
    ((char *)enc)[1] = (value & 0xff);
    ((char *)enc)[2] = (value >> 8) & 0xff;
    ((char *)enc)[3] = (value >> 16) & 0xff;
    ((char *)enc)[4] = (value >> 24) & 0xff;
    return 5;
  }
  return 0;
}