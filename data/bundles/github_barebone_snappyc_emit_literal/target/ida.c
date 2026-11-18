char *__cdecl emit_literal(char *op, const char *literal, int len, bool allow_fast_path)
{
  char *v4; // rax
  int count; // [rsp+Ch] [rbp-34h]
  int n; // [rsp+1Ch] [rbp-24h]
  char *opa; // [rsp+30h] [rbp-10h]

  n = len - 1;
  if ( len - 1 >= 60 )
  {
    count = 0;
    opa = op + 1;
    while ( n > 0 )
    {
      v4 = opa++;
      *v4 = n;
      n >>= 8;
      ++count;
    }
    if ( count < 1 )
      _assert_fail("!(!(count >= 1))", "func.c", 0x247u, "char *emit_literal(char *, const char *, int, _Bool)");
    if ( count > 4 )
      _assert_fail("!(!(count <= 4))", "func.c", 0x248u, "char *emit_literal(char *, const char *, int, _Bool)");
    *op = 4 * (count + 59);
    goto LABEL_14;
  }
  opa = op + 1;
  *op = 4 * n;
  if ( !allow_fast_path || len > 16 )
  {
LABEL_14:
    memcpy(opa, literal, len);
    return &opa[len];
  }
  unaligned_copy64(literal, opa);
  unaligned_copy64(literal + 8, op + 9);
  return &opa[len];
}