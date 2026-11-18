char *jvp_literal_number_literal(jv n)
{
  if (!((((n).kind_flags & (jv_flags)(JV_IS_NUMBER)) == (JV_IS_NUMBER))))
    jv_assert_failed("JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL)", "/work/harness.c", 293, __PRETTY_FUNCTION__);
  struct decNumber *dec = jvp_number_dec(n);
  struct jvp_literal_number *lit = jvp_literal_number(n);
  if (dec->bits & (0x0001 | 0x0002 | 0x0004))
    return "null";
  if (dec->bits & (0x0008))
    return ((void *)0);
  if (lit->literal_data == ((void *)0))
  {
    lit->literal_data = jvp_literal_number_data(dec->digits + 14);
    jvp_literal_number_set(dec, lit->literal_data);
  }
  return lit->literal_data;
}