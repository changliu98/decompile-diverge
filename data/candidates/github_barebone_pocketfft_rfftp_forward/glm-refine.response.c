int __cdecl rfftp_forward(rfftp_plan plan, double *c, double fct)
{
  double *p1;
  double *p2;
  double *tmp;
  double *ch;
  size_t n;
  size_t l1;
  size_t nf;
  size_t k1;
  size_t k;
  size_t ip;
  size_t ido;

  if (plan->length == 1)
    return 0;

  n = plan->length;
  l1 = plan->length;
  nf = plan->nfct;

  ch = (double *)malloc(8 * n);
  if (!ch)
    return -1;

  p1 = c;
  p2 = ch;

  // Iterate over the factors in reverse order
  for (k1 = 0; k1 < nf; ++k1)
  {
    k = nf - k1 - 1;
    ip = plan->fct[k].fct;
    ido = n / l1;
    l1 /= ip;

    switch (ip)
    {
      case 2:
        radf2(ido, l1, p1, p2, plan->fct[k].tw);
        break;
      case 3:
        radf3(ido, l1, p1, p2, plan->fct[k].tw);
        break;
      case 4:
        radf4(ido, l1, p1, p2, plan->fct[k].tw);
        break;
      case 5:
        radf5(ido, l1, p1, p2, plan->fct[k].tw);
        break;
      default:
        radfg(ido, ip, l1, p1, p2, plan->fct[k].tw, plan->fct[k].tws);
        // Swap pointers
        tmp = p1;
        p1 = p2;
        p2 = tmp;
        break;
    }

    // Swap pointers for the next iteration
    tmp = p1;
    p1 = p2;
    p2 = tmp;
  }

  copy_and_norm(c, p1, n, fct);
  free(ch);

  return 0;
}