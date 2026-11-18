static int test_and_set_bit(long nr , unsigned long *addr )
{ int __cil_tmp3 ;
  int __cil_tmp4 ;
  int __cil_tmp5 ;
  int __cil_tmp6 ;

  {
  {
# 29 "concatenated.c"
  __cil_tmp3 = (int )nr;
# 29 "concatenated.c"
  __cil_tmp4 = (unsigned long )(1) << __cil_tmp3;
# 29 "concatenated.c"
  __cil_tmp5 = (int )__cil_tmp4;
# 29 "concatenated.c"
  __cil_tmp6 = *addr ^ __cil_tmp5;
# 29 "concatenated.c"
  *addr = (unsigned long )__cil_tmp6;
  }
  {
# 30 "concatenated.c"
  return ((int )((int volatile )*addr & (int volatile )1));
  }
}
}