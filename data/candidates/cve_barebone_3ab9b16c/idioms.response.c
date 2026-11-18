void sycc420_to_rgb(struct opj_image *img)
{
  int i; int j;
  int upba;
  int offset;
  int upb;
  unsigned int maxw;
  unsigned int maxh;
  int *y; int *ya; int *yb;
  int *cb; int *cr;
  int *r; int *ra; int *rb;
  int *g; int *ga; int *gb;
  int *b; int *ba; int *bb;
  int *ny; int *nya; int *nyb;
  int *nr; int *nra; int *nrb;
  int *ng; int *nga; int *ngb;
  int *nb; int *nba; int *nbb;
  upba = img->comps[0].prec;
  offset = 1 << (upba - 1);
  upb = (1 << upba) - 1;
  maxw = img->comps[0].w;
  maxh = img->comps[0].h;
  y = img->comps[0].data;
  cb = img->comps[1].data;
  cr = img->comps[2].data;
  r = opj_malloc(maxw * maxh * sizeof(int));
  ra = r;
  g = opj_malloc(maxw * maxh * sizeof(int));
  ga = g;
  b = opj_malloc(maxw * maxh * sizeof(int));
  ba = b;
  if (r == ((void *)0) || g == ((void *)0) || b == ((void *)0))
  {
    if (r != ((void *)0))
      opj_free(r);
    if (g != ((void *)0))
      opj_free(g);
    if (b != ((void *)0))
      opj_free(b);
    return;
  }
  for (i = 0; i < (maxh & ~1); i += 2)
  {
    ny = y + maxw;
    nr = r + maxw;
    ng = g + maxw;
    nb = b + maxw;
    for (j = 0; j < (maxw & ~1); j += 2)
    {
      decompress(offset, upb, y[0], cb[0], cr[0], r, g, b);
      ya = y + 1;
      ra = r + 1;
      ga = g + 1;
      ba = b + 1;
      decompress(offset, upb, ya[0], cb[0], cr[0], ra, ga, ba);
      y = ya + 1;
      r = ra + 1;
      g = ga + 1;
      b = ba + 1;
      decompress(offset, upb, ny[0], cb[0], cr[0], nr, ng, nb);
      nya = ny + 1;
      nra = nr + 1;
      nga = ng + 1;
      nba = nb + 1;
      decompress(offset, upb, nya[0], cb[0], cr[0], nra, nga, nba);
      ny = nya + 1;
      nr = nra + 1;
      ng = nga + 1;
      nb = nba + 1;
      cb++;
      cr++;
    }
    if (j < maxw)
    {
      decompress(offset, upb, y[0], cb[0], cr[0], r, g, b);
      y++;
      r++;
      g++;
      b++;
    }
    y += maxw;
    r += maxw;
    g += maxw;
    b += maxw;
  }
  if (i < maxh)
  {
    for (j = 0; j < (maxw & ~1); j += 2)
    {
      decompress(offset, upb, y[0], cb[0], cr[0], r, g, b);
      yb = y + 1;
      rb = r + 1;
      gb = g + 1;
      bb = b + 1;
      decompress(offset, upb, yb[0], cb[0], cr[0], rb, gb, bb);
      y = yb + 1;
      r = rb + 1;
      g = gb + 1;
      b = bb + 1;
      cb++;
      cr++;
    }
    if (j < maxw)
      decompress(offset, upb, y[0], cb[0], cr[0], r, g, b);
  }
  opj_image_set_data(img->comps[0].data);
  img->comps[0].data = ra;
  opj_image_set_data(img->comps[1].data);
  img->comps[1].data = ga;
  opj_image_set_data(img->comps[2].data);
  img->comps[2].data = ba;
  img->comps[1].w = maxw;
  img->comps[1].h = maxh;
  img->comps[2].w = maxw;
  img->comps[2].h = maxh;
  img->comps[1].dx = img->comps[0].dx;
  img->comps[2].dx = img->comps[0].dx;
  img->comps[1].dy = img->comps[0].dy;
  img->comps[2].dy = img->comps[0].dy;
}