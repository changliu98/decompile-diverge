static const char *jvp_literal_number_literal(jv n) {
  do { if (!(JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL))) ___assert_fail("JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL)", "harness.c", 301, "const char *jvp_literal_number_literal(jv)"); } while (0);
  decNumber *dn = jvp_dec_number_ptr(n);
  struct jvp_literal_number *ln = jvp_literal_number_ptr(n);
  const char *ret;
  if ((dn->bits & (0x20|0x10)) != 0) {
    ret = "null";
  } else if ((dn->bits & 0x40) != 0) {
    ret = NULL;
  } else {
    if (ln->literal == NULL) {
      int len = jvp_dec_number_ptr(n)->exponent + 14;
      ln->literal = jv_mem_alloc(len);
      decNumberToString(dn, ln->literal);
    }
    ret = ln->literal;
  }
  return ret;
}