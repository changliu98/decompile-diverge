const char *__cdecl jvp_literal_number_literal(jv n)
{
  decNumber *v1; // rax
  jvp_literal_number *plit; // [rsp+8h] [rbp-28h]
  decNumber *pdec; // [rsp+10h] [rbp-20h]

  if ( n.kind_flags != 148 )
    __assert_fail(
      "JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL)",
      "/work/harness.c",
      0x12Du,
      "const char *jvp_literal_number_literal(jv)");
  pdec = jvp_dec_number_ptr(n);
  plit = jvp_literal_number_ptr(n);
  if ( (pdec->bits & 0x30) != 0 )
    return "null";
  if ( (pdec->bits & 0x40) != 0 )
    return 0LL;
  if ( !plit->literal_data )
  {
    v1 = jvp_dec_number_ptr(n);
    plit->literal_data = (char *)jv_mem_alloc(v1->digits + 14);
    decNumberToString(pdec, plit->literal_data);
  }
  return plit->literal_data;
}