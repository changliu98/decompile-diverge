void gf_free(gf_t *gf)
{
  unsigned int i;
  gf_internal_t *h;

  h = (gf_internal_t *) gf;
  if (h == NULL) return;

  for (i = 0; i < h->base_gf->degree; i++) {
    if (h->base_gf->div[i].quotient != NULL) gf_free(h->base_gf->div[i].quotient);
  }
  if (h->base_gf->div != NULL) gf_free(h->base_gf->div);

  if (h != NULL) gf_free(h);
}