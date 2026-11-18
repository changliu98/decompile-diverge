static int cfftp_comp_twiddle (cfftp_plan plan)
  {
  size_t length=plan->length;
  double *twid = RALLOC(double, 2*length);
  if (!twid) return -1;
  sincos_2pibyn(length, twid);
  size_t l1=1;
  size_t memofs=0;
  for (size_t k=0; k<plan->nfct; ++k)
    {
    size_t ip=plan->fct[k].fct, ido= length/(l1*ip);
    plan->fct[k].tw=plan->mem+memofs;
    memofs+=(ip-1)*(ido-1);
    for (size_t j=1; j<ip; ++j)
      for (size_t i=1; i<ido; ++i)
        {
        plan->fct[k].tw[(j-1)*(ido-1)+i-1].r = twid[2*j*l1*i];
        plan->fct[k].tw[(j-1)*(ido-1)+i-1].i = twid[2*j*l1*i+1];
        }
    if (ip>11)
      {
      plan->fct[k].tws=plan->mem+memofs;
      memofs+=ip;
      for (size_t j=0; j<ip; ++j)
        {
        plan->fct[k].tws[j].r = twid[2*j*l1*ido];
        plan->fct[k].tws[j].i = twid[2*j*l1*ido+1];
        }
      }
    l1*=ip;
    }
  DEALLOC(twid);
  return 0;
  }