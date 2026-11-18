const char *jvp_literal_number_literal(jv_nontrivial value) {
  assert(jv_get_kind(value, JV_KIND_NUMBER));
  decNumber *dec = jvp_dec_number_ptr(value);
  struct jv_number_literal *lit = jvp_literal_number_ptr(value);
  if (dec->bits & (0x20 | 0x10)) return "null";
  if (dec->bits & 0x40) return 0;
  if (!lit->literal) {
    lit->literal = jv_mem_alloc(dec->digits + 14);
    decNumberToString(dec, lit->literal);
  }
  return lit->literal;
}