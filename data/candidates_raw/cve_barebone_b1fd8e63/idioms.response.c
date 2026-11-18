void gf_box_free(struct _GF_Box *box)
{
  if (box == ((void *)0))
    return;
  for (unsigned int i = 0; i < box->n; i++)
  {
    if (box->data[i].data != ((void *)0))
      gf_free(box->data[i].data);
  }
  if (box->data != ((void *)0))
    gf_free(box->data);
  gf_free(box);
}