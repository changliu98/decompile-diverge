int cfftp_precomp(struct cfftp_plan *plan)
{
  struct cfftp_twid *twid;
  unsigned long length = plan->length;
  unsigned long i; unsigned long j; unsigned long k;
  unsigned long fct; unsigned long fctlen; unsigned long fctlen1;
  unsigned long fctlen2; unsigned long fctlen21;
  if ((twid = (struct cfftp_twid *)malloc(sizeof(cfftp_twid)*length)) == ((void *)0))
    return -1;
  sincos_2pibyn(length, twid);
  fctlen = 1;
  fctlen1 = 0;
  for (fct = 0; fct < plan->nfct; fct++)
  {
    fctlen2 = plan->fct[fct].fct;
    fctlen21 = length / (fctlen2 * fctlen);
    plan->fct[fct].tw = &plan->mem[fctlen1];
    fctlen1 += (fctlen2 - 1)*(fctlen21 - 1);
    for (i = 1; i < fctlen2; i++)
    {
      for (j = 1; j < fctlen21; j++)
      {
        plan->fct[fct].tw[(i-1)*(fctlen21 - 1)+j-1].r = twid[i*fctlen*2*j].r;
        plan->fct[fct].tw[(i-1)*(fctlen21 - 1)+j-1].i = twid[i*fctlen*2*j].i;
      }
    }
    if (fctlen2 > 12)
    {
      plan->fct[fct].tws = &plan->mem[fctlen1];
      fctlen1 += fctlen2;
      for (k = 0; k < fctlen2; k++)
      {
        plan->fct[fct].tws[k].r = twid[k*fctlen21*2].r;
        plan->fct[fct].tws[k].i = twid[k*fctlen21*2].i;
      }
    }
    fctlen *= fctlen2;
  }
  free(twid);
  return 0;
}