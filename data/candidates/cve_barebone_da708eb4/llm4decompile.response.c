const char* jvp_literal_number_literal(jv n) {
  decNumber *dn;
  jvp_literal_number *plit;
  do { if (!(!JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL))) { __assert_fail("JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL)", "/work/harness.c", 301, "const char *jvp_literal_number_literal(jv)"); } } while (0);
  dn = jvp_dec_number_ptr(n);
  plit = jvp_literal_number_ptr(n);
  if (dn->bits & 0x20 || dn->bits & 0x10) {
    return "null";
  } else if (dn->bits & 0x40) {
    return NULL;
  } else if (plit->literal_data != NULL) {
    return plit->literal_data;
  } else {
    size_t len = jvp_dec_number_ptr(n)->digits + 14;
    plit->literal_data = jv_mem_alloc(len);
    decNumberToString(dn, plit->literal_data);
    return plit->literal_data;
  }
}