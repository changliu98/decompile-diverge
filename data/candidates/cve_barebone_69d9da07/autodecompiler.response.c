int opj_pi_next_rpcl(opj_tcd_pass_t *pass)
{
 int resno, level, compno, flag;
 unsigned int l, pos, n;
 opj_tcd_layercomp_t *comp = NULL;
 opj_tcd_resolution_t *res = NULL;

 if (!pass->is_empty) {
  goto LABEL_SKIP;
 }

 pass->is_empty = 0;

 pass->len = 0;
 pass->dist = 0;

 for (compno = 0; compno < pass->numcomps; compno++) {
  comp = &pass->layercomp[compno];
  for (resno = 0; resno < comp->numresolutions; resno++) {
   res = &comp->resolutions[resno];

   l = (unsigned int)(comp->numbps *
                      (1 << ((comp->prec + res->numcomps +
                              1) - 1 - resno)));
   n = (unsigned int)(comp->w * (1 << ((comp->prec + res->numcomps +
                                       1) - 1 - resno)));

   if (!pass->dist) {
    pos = l;
   } else {
    pos = opj_uint_min(pass->dist, l);
   }
   pass->dist = pos;

   if (!pass->len) {
    flag = n;
   } else {
    flag = opj_uint_min(pass->len, n);
   }
   pass->len = flag;
  }
 }

LABEL_SKIP:

 if (!pass->is_reversible) {
  pass->rx = pass->xref;
  pass->ry = pass->yref;
  pass->cx = pass->cxref;
  pass->cy = pass->cyref;
 }

 pass->c = pass->compno;

 while (pass->c < pass->numcomps) {

  pass->x = pass->rx;

  while (pass->x < pass->cx) {

   pass->y = pass->ry;

   while (pass->y < pass->cy) {

    pass->compno++;

    if (pass->compno >= pass->numcomps) {
     break;
    }

    comp = &pass->layercomp[pass->compno];

    if (pass->c >= comp->numresolutions) {
     continue;
    }

    res = &comp->resolutions[pass->c];

    level = comp->prec - 1 - pass->c;

    {
     int w = opj_int_ceildiv(pass->xref,
                             (opj_int32)(comp->w << level));
     int h = opj_int_ceildiv(pass->yref,
                             (opj_int32)(comp->h << level));

     int w1 = opj_int_ceildiv(pass->cxref,
                              (opj_int32)(comp->w << level));
     int h1 = opj_int_ceildiv(pass->cyref,
                              (opj_int32)(comp->h << level));

     int rx = res->x0 + level;
     int ry = res->y0 + level;

     if (((pass->x % (comp->w << rx)) == 0) ||
         ((pass->x == pass->xref) && ((h << level) % (1 << ry)) == 0)) {
      continue;
     }

     if (((pass->y % (comp->h << ry)) == 0) ||
         ((pass->y == pass->yref) && ((w << level) % (1 << rx)) == 0)) {
      continue;
     }

     if ((!res->numbps) || (!res->data)) {
      continue;
     }

     if ((w != w1) || (h != h1)) {
      int prci, prcj;

      prci = opj_int_floordivpow2(
               opj_int_ceildiv(pass->xref, (opj_int32)(comp->w << level)),
               res->x0) -
             opj_int_floordivpow2(w, res->x0);

      prcj = opj_int_floordivpow2(
               opj_int_ceildiv(pass->yref, (opj_int32)(comp->h << level)),
               res->y0) -
             opj_int_floordivpow2(h, res->y0);

      pass->pos = prci + prcj * res->numcomps;

      pass->i = pass->inc;

      while (pass->i < pass->size) {

       pos = pass->pos * pass->stride + pass->i;

       if (!((short*)pass->data)[pos]) {
        ((short*)pass->data)[pos] = 1;
        flag = 1;
        break;
       }

       pass->i++;
      }
     }

     break;
    }
   }

   if (pass->compno < pass->numcomps) {
    break;
   }

   pass->y += pass->dist - (pass->y % pass->dist);
  }

  if (pass->compno < pass->numcomps) {
   break;
  }

  pass->c++;
 }

 return flag;
}