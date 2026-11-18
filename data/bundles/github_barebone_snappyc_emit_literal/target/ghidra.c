char * emit_literal(char *op,char *literal,int len,_Bool allow_fast_path)

{
  int count;
  char *base;
  int n;
  _Bool allow_fast_path_local;
  int len_local;
  char *literal_local;
  char *op_local;
  
  n = len + -1;
  if (n < 0x3c) {
    op_local = op + 1;
    *op = (char)n * '\x04';
    if ((allow_fast_path) && (len < 0x11)) {
      unaligned_copy64(literal,op_local);
      unaligned_copy64(literal + 8,op + 9);
      return op_local + len;
    }
  }
  else {
    count = 0;
    op_local = op;
    for (; op_local = op_local + 1, 0 < n; n = n >> 8) {
      *op_local = (char)n;
      count = count + 1;
    }
    if (count < 1) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("!(!(count >= 1))","func.c",0x247,
                    "char *emit_literal(char *, const char *, int, _Bool)");
    }
    if (4 < count) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("!(!(count <= 4))","func.c",0x248,
                    "char *emit_literal(char *, const char *, int, _Bool)");
    }
    *op = ((char)count + ';') * '\x04';
  }
  memcpy(op_local,literal,(long)len);
  return op_local + len;
}