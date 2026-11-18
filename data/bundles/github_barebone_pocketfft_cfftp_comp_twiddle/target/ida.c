int __cdecl cfftp_comp_twiddle(cfftp_plan plan)
{
  size_t j_0; // [rsp+0h] [rbp-60h]
  size_t i; // [rsp+8h] [rbp-58h]
  size_t j; // [rsp+10h] [rbp-50h]
  size_t ido; // [rsp+18h] [rbp-48h]
  size_t ip_0; // [rsp+20h] [rbp-40h]
  size_t k; // [rsp+28h] [rbp-38h]
  size_t memofs; // [rsp+30h] [rbp-30h]
  size_t l1; // [rsp+38h] [rbp-28h]
  double *twid; // [rsp+40h] [rbp-20h]
  size_t length; // [rsp+48h] [rbp-18h]

  length = plan->length;
  twid = (double *)malloc(16 * plan->length);
  if ( !twid )
    return -1;
  sincos_2pibyn(length, twid);
  l1 = 1LL;
  memofs = 0LL;
  for ( k = 0LL; k < plan->nfct; ++k )
  {
    ip_0 = plan->fct[k].fct;
    ido = length / (ip_0 * l1);
    plan->fct[k].tw = &plan->mem[memofs];
    memofs += (ido - 1) * (ip_0 - 1);
    for ( j = 1LL; j < ip_0; ++j )
    {
      for ( i = 1LL; i < ido; ++i )
      {
        plan->fct[k].tw[i - 1 + (ido - 1) * (j - 1)].r = twid[i * l1 * 2 * j];
        plan->fct[k].tw[i - 1 + (ido - 1) * (j - 1)].i = twid[i * l1 * 2 * j + 1];
      }
    }
    if ( ip_0 > 0xB )
    {
      plan->fct[k].tws = &plan->mem[memofs];
      memofs += ip_0;
      for ( j_0 = 0LL; j_0 < ip_0; ++j_0 )
      {
        plan->fct[k].tws[j_0].r = twid[ido * l1 * 2 * j_0];
        plan->fct[k].tws[j_0].i = twid[ido * l1 * 2 * j_0 + 1];
      }
    }
    l1 *= ip_0;
  }
  free(twid);
  return 0;
}