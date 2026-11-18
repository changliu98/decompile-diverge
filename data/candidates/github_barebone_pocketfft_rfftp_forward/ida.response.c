int __cdecl rfftp_forward(rfftp_plan plan, double *c, double fct)
{
  double *tmp__0; // [rsp+10h] [rbp-80h]
  double *tmp_; // [rsp+18h] [rbp-78h]
  size_t ido; // [rsp+20h] [rbp-70h]
  size_t ip_0; // [rsp+28h] [rbp-68h]
  size_t k; // [rsp+30h] [rbp-60h]
  size_t k1_0; // [rsp+38h] [rbp-58h]
  double *p2; // [rsp+40h] [rbp-50h]
  double *p1; // [rsp+48h] [rbp-48h]
  double *ch_0; // [rsp+50h] [rbp-40h]
  size_t nf; // [rsp+58h] [rbp-38h]
  size_t l1; // [rsp+60h] [rbp-30h]
  size_t n; // [rsp+68h] [rbp-28h]

  if ( plan->length == 1 )
    return 0;
  n = plan->length;
  l1 = plan->length;
  nf = plan->nfct;
  ch_0 = (double *)malloc(8 * plan->length);
  if ( !ch_0 )
    return -1;
  p1 = c;
  p2 = ch_0;
  for ( k1_0 = 0LL; k1_0 < nf; ++k1_0 )
  {
    k = nf - k1_0 - 1;
    ip_0 = plan->fct[k].fct;
    ido = n / l1;
    l1 /= ip_0;
    switch ( ip_0 )
    {
      case 4uLL:
        radf4(ido, l1, p1, p2, plan->fct[k].tw);
        break;
      case 2uLL:
        radf2(ido, l1, p1, p2, plan->fct[k].tw);
        break;
      case 3uLL:
        radf3(ido, l1, p1, p2, plan->fct[k].tw);
        break;
      case 5uLL:
        radf5(ido, l1, p1, p2, plan->fct[k].tw);
        break;
      default:
        radfg(ido, ip_0, l1, p1, p2, plan->fct[k].tw, plan->fct[k].tws);
        tmp_ = p1;
        p1 = p2;
        p2 = tmp_;
        break;
    }
    tmp__0 = p1;
    p1 = p2;
    p2 = tmp__0;
  }
  copy_and_norm(c, p1, n, fct);
  free(ch_0);
  return 0;
}