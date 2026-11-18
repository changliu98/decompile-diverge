int rdbEncodeInteger(rio *rdb, long value) {
 unsigned char buf[11];
 int n;

 if (value < 0) {
  value = -value;
  buf[0] = (RDB_ENCVAL << 6) | RDB_ENC_INT64;
  n = 1;
 }
 else {
  buf[0] = 0;
  n = 1;
 }

 if (value < 128) {
  buf[n++] = value;
 }
 else if (value < 16384) {
  buf[n++] = (RDB_ENCVAL << 6) | (value >> 8);
  buf[n++] = value & 0xff;
 }
 else if (value < 4194304) {
  buf[n++] = (RDB_ENCVAL << 6) | (value >> 16);
  buf[n++] = (value >> 8) & 0xff;
  buf[n++] = value & 0xff;
 }
 else if (value < 1073741824) {
  buf[n++] = (RDB_ENCVAL << 6) | (value >> 24);
  buf[n++] = (value >> 16) & 0xff;
  buf[n++] = (value >> 8) & 0xff;
  buf[n++] = value & 0xff;
 }
 else {
  assert__bench(value < (1ll << 63));
  buf[0] |= (RDB_ENCVAL << 6) | RDB_ENC_INT64;
  buf[n++] = (value >> 32) & 0xff;
  buf[n++] = (value >> 24) & 0xff;
  buf[n++] = (value >> 16) & 0xff;
  buf[n++] = (value >> 8) & 0xff;
  buf[n++] = value & 0xff;
 }

 assert__bench(n <= 11);

 return rioWrite(rdb, buf, n);
}