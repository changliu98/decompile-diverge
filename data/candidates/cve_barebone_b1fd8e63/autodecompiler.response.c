void gitn_box_del(gf_t *gf)
{
  unsigned int i;
  gf_internal_t *h;

  h = (gf_internal_t *) gf;
  if (h == NULL) return;

  for (i = 0; i < h->base_gf->degree; i++) {
    if (h->base_gf->div[i].quotient != NULL) gitn_box_del(h->base_gf->div[i].quotient);
  }
  if (h->base_gf->div != NULL) gitn_box_del(h->base_gf->div);

  if (h != NULL) gitn_box_del(h);
}