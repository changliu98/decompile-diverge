void __cdecl sycc420_to_rgb(opj_image_t *img)
{
  unsigned int j; // [rsp+14h] [rbp-8Ch]
  unsigned int ja; // [rsp+14h] [rbp-8Ch]
  unsigned int i; // [rsp+18h] [rbp-88h]
  int upba; // [rsp+1Ch] [rbp-84h]
  int upb; // [rsp+1Ch] [rbp-84h]
  int offset; // [rsp+20h] [rbp-80h]
  unsigned int maxh; // [rsp+28h] [rbp-78h]
  unsigned int maxw; // [rsp+2Ch] [rbp-74h]
  int *ny; // [rsp+30h] [rbp-70h]
  int *nya; // [rsp+30h] [rbp-70h]
  int *cr; // [rsp+38h] [rbp-68h]
  int *cb; // [rsp+40h] [rbp-60h]
  int *y; // [rsp+48h] [rbp-58h]
  int *ya; // [rsp+48h] [rbp-58h]
  int *yb; // [rsp+48h] [rbp-58h]
  int *nb; // [rsp+50h] [rbp-50h]
  int *nba; // [rsp+50h] [rbp-50h]
  int *ng; // [rsp+58h] [rbp-48h]
  int *nga; // [rsp+58h] [rbp-48h]
  int *nr; // [rsp+60h] [rbp-40h]
  int *nra; // [rsp+60h] [rbp-40h]
  int *b; // [rsp+68h] [rbp-38h]
  int *ba; // [rsp+68h] [rbp-38h]
  int *bb; // [rsp+68h] [rbp-38h]
  int *g; // [rsp+70h] [rbp-30h]
  int *ga; // [rsp+70h] [rbp-30h]
  int *gb; // [rsp+70h] [rbp-30h]
  int *r; // [rsp+78h] [rbp-28h]
  int *ra; // [rsp+78h] [rbp-28h]
  int *rb; // [rsp+78h] [rbp-28h]
  int *d2; // [rsp+80h] [rbp-20h]
  int *d1; // [rsp+88h] [rbp-18h]
  int *d0; // [rsp+90h] [rbp-10h]

  upba = img->comps->prec;
  offset = 1 << (upba - 1);
  upb = (1 << upba) - 1;
  maxw = img->comps->w;
  maxh = img->comps->h;
  y = img->comps->data;
  cb = img->comps[1].data;
  cr = img->comps[2].data;
  r = (int *)malloc(4LL * maxh * maxw);
  d0 = r;
  g = (int *)malloc(4LL * maxh * maxw);
  d1 = g;
  b = (int *)malloc(4LL * maxh * maxw);
  d2 = b;
  if ( r && g && b )
  {
    for ( i = 0; i < (maxh & 0xFFFFFFFE); i += 2 )
    {
      ny = &y[maxw];
      nr = &r[maxw];
      ng = &g[maxw];
      nb = &b[maxw];
      for ( j = 0; j < (maxw & 0xFFFFFFFE); j += 2 )
      {
        sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
        ya = y + 1;
        ra = r + 1;
        ga = g + 1;
        ba = b + 1;
        sycc_to_rgb(offset, upb, *ya, *cb, *cr, ra, ga, ba);
        y = ya + 1;
        r = ra + 1;
        g = ga + 1;
        b = ba + 1;
        sycc_to_rgb(offset, upb, *ny, *cb, *cr, nr, ng, nb);
        nya = ny + 1;
        nra = nr + 1;
        nga = ng + 1;
        nba = nb + 1;
        sycc_to_rgb(offset, upb, *nya, *cb, *cr, nra, nga, nba);
        ny = nya + 1;
        nr = nra + 1;
        ng = nga + 1;
        nb = nba + 1;
        ++cb;
        ++cr;
      }
      if ( j < maxw )
      {
        sycc_to_rgb(offset, upb, *y++, *cb, *cr, r++, g++, b++);
        sycc_to_rgb(offset, upb, *ny, *cb++, *cr++, nr, ng, nb);
      }
      y += maxw;
      r += maxw;
      g += maxw;
      b += maxw;
    }
    if ( i < maxh )
    {
      for ( ja = 0; ja < (maxw & 0xFFFFFFFE); ja += 2 )
      {
        sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
        yb = y + 1;
        rb = r + 1;
        gb = g + 1;
        bb = b + 1;
        sycc_to_rgb(offset, upb, *yb, *cb, *cr, rb, gb, bb);
        y = yb + 1;
        r = rb + 1;
        g = gb + 1;
        b = bb + 1;
        ++cb;
        ++cr;
      }
      if ( ja < maxw )
        sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
    }
    free(img->comps->data);
    img->comps->data = d0;
    free(img->comps[1].data);
    img->comps[1].data = d1;
    free(img->comps[2].data);
    img->comps[2].data = d2;
    img->comps[1].w = maxw;
    img->comps[1].h = maxh;
    img->comps[2].w = maxw;
    img->comps[2].h = maxh;
    img->comps[1].dx = img->comps->dx;
    img->comps[2].dx = img->comps->dx;
    img->comps[1].dy = img->comps->dy;
    img->comps[2].dy = img->comps->dy;
  }
  else
  {
    if ( r )
      free(r);
    if ( g )
      free(g);
    if ( b )
      free(b);
  }
}