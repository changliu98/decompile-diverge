WARN_UNUSED_RESULT
static int rfftp_forward(rfftp_plan plan, double c[], double fct)
  {
  if (plan->length==1) return 0;
  size_t n=plan->length;
  size_t l1=n, nf=plan->nfct;
  double *ch = RALLOC(double, n);
  if (!ch) return -1;
  double *p1=c, *p2=ch;

  for(size_t k1=0; k1<nf;++k1)
    {
    size_t k=nf-k1-1;
    size_t ip=plan->fct[k].fct;
    size_t ido=n / l1;
    l1 /= ip;
    if(ip==4)
      radf4(ido, l1, p1, p2, plan->fct[k].tw);
    else if(ip==2)
      radf2(ido, l1, p1, p2, plan->fct[k].tw);
    else if(ip==3)
      radf3(ido, l1, p1, p2, plan->fct[k].tw);
    else if(ip==5)
      radf5(ido, l1, p1, p2, plan->fct[k].tw);
    else
      {
      radfg(ido, ip, l1, p1, p2, plan->fct[k].tw, plan->fct[k].tws);
      SWAP (p1,p2,double *);
      }
    SWAP (p1,p2,double *);
    }
  copy_and_norm(c,p1,n,fct);
  DEALLOC(ch);
  return 0;
  }