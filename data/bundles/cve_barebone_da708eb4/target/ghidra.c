char * jvp_literal_number_literal(jv n)

{
  decNumber *dn;
  jvp_literal_number *pjVar1;
  decNumber *pdVar2;
  char *pcVar3;
  int len;
  jvp_literal_number *plit;
  decNumber *pdec;
  jv n_local;
  char *local_10;
  
  n_local.kind_flags = n.kind_flags;
  if (n_local.kind_flags == 0x94) {
    dn = jvp_dec_number_ptr(n);
    pjVar1 = jvp_literal_number_ptr(n);
    if ((dn->bits & 0x30) == 0) {
      if ((dn->bits & 0x40) == 0) {
        if (pjVar1->literal_data == (char *)0x0) {
          pdVar2 = jvp_dec_number_ptr(n);
          pcVar3 = jv_mem_alloc((long)(pdVar2->digits + 0xe));
          pjVar1->literal_data = pcVar3;
          decNumberToString(dn,pjVar1->literal_data);
        }
        local_10 = pjVar1->literal_data;
      }
      else {
        local_10 = (char *)0x0;
      }
    }
    else {
      local_10 = "null";
    }
    return local_10;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL)","/work/harness.c",0x12d,
                "const char *jvp_literal_number_literal(jv)");
}