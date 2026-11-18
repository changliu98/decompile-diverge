static int jpc_dec_process_siz(jpc_dec_t *dec, jpc_siz_t *siz) {
  int i;
  int j;
  int htile;
  int vtile;
  jpc_tile_t *tile;
  jpc_cp_t *cp;
  jpc_tilecomp_t *tc;
  dec->cblkwidth = siz->m.CblkWidth;
  dec->cblkheight = siz->m.CblkHeight;
  dec->cblkstride = siz->m.CblkStripHeight;
  dec->xblkwidth = siz->m.XblkWidth;
  dec->xblkstride = siz->m.XblkStripWidth;
  dec->numcomps = siz->m.NumComps;
  if (!(dec->cp = jpc_dec_cp_create(dec->numcomps))) {
    return -1;
  }
  if (!(dec->cps = jas_alloc2(dec->numcomps, sizeof(jpc_cp_t)))) {
    return -1;
  }
  for (i = 0, cp = dec->cps; i < dec->numcomps; ++i, ++cp) {
    cp->id = siz->m.CompSpec[i].id;
    cp->qntsty = siz->m.CompSpec[i].qntsty ? 1 : 0;
    cp->dx = siz->m.CompSpec[i].dx;
    cp->dy = siz->m.CompSpec[i].dy;
    cp->numhparts = (dec->cblkheight + cp->dx - 1) / cp->dx -
                    (dec->cblkwidth + cp->dx - 1) / cp->dx;
    cp->numvparts = (dec->cblkstride + cp->dy - 1) / cp->dy -
                    (dec->xblkwidth + cp->dy - 1) / cp->dy;
    cp->hpart = 0;
    cp->vpart = 0;
  }
  dec->curtileno = 0;
  dec->numhtiles = (dec->xblkstride + dec->cblkheight - dec->xblkwidth - 1) /
                   dec->xblkstride;
  dec->numvtiles = (dec->yblkstride + dec->cblkstride - dec->yblkwidth - 1) /
                   dec->yblkstride;
  dec->numtiles = dec->numhtiles * dec->numvtiles;
  if (jas_getdbglevel() >= 10) {
    jas_eprintf("numtiles = %d; numhtiles = %d; numvtiles = %d;\n",
                dec->numtiles, dec->numhtiles, dec->numvtiles);
  }
  if (!(dec->tiles = jas_alloc2(dec->numtiles, sizeof(jpc_tile_t)))) {
    return -1;
  }
  for (j = 0, tile = dec->tiles; j < dec->numtiles; ++j, ++tile) {
    htile = j % dec->numhtiles;
    vtile = j / dec->numhtiles;
    tile->xblkno = 0;
    tile->yblkno = 0;
    tile->xblkorg = (htile * dec->xblkstride + dec->xblkwidth > dec->cblkwidth)
                        ? htile * dec->xblkstride + dec->xblkwidth
                        : dec->cblkwidth;
    tile->yblkorg = (vtile * dec->yblkstride + dec->yblkwidth > dec->xblkwidth)
                        ? vtile * dec->yblkstride + dec->yblkwidth
                        : dec->xblkwidth;
    tile->xblkend = ((htile + 1) * dec->xblkstride + dec->xblkwidth <
                     dec->cblkheight)
                        ? (htile + 1) * dec->xblkstride + dec->xblkwidth
                        : dec->cblkheight;
    tile->yblkend = ((vtile + 1) * dec->yblkstride + dec->yblkwidth <
                     dec->cblkstride)
                        ? (vtile + 1) * dec->yblkstride + dec->yblkwidth
                        : dec->cblkstride;
    tile->xblkorg2 = 0;
    tile->yblkorg2 = 0;
    tile->xblkend2 = 0;
    tile->yblkend2 = 0;
    tile->flags = 0;
    if (!(tile->tcs = jas_alloc2(dec->numcomps, sizeof(jpc_tilecomp_t)))) {
      return -1;
    }
    for (i = 0, cp = dec->cps, tc = tile->tcs; i < dec->numcomps;
         ++i, ++cp, ++tc) {
      tc->hpartorg = 0;
      tc->vpartorg = 0;
      tc->hpartend = 0;
      tc->hpartorg2 = (tile->xblkorg + cp->dx - 1) / cp->dx;
      tc->vpartorg2 = (tile->yblkorg + cp->dy - 1) / cp->dy;
      tc->hpartend2 = (tile->xblkend + cp->dx - 1) / cp->dx;
      tc->vpartend2 = (tile->yblkend + cp->dy - 1) / cp->dy;
      tc->flags = 0;
    }
  }
  dec->curcompno = 0;
  dec->curcblkno = 4;
  return 0;
}