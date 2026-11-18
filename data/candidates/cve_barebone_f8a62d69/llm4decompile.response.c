int jpc_dec_process_siz(jpc_dec_t *dec, jpc_ms_t *ms)
{
 jpc_dec_cmpt_t *cmpt;
 jpc_dec_tile_t *tile;
 jpc_dec_tcomp_t *tcomp;
 int i, j, k;
 int htileno, vtileno;

 dec->xstart = ms->parms.siz.xoff;
 dec->ystart = ms->parms.siz.yoff;
 dec->xend = ms->parms.siz.width;
 dec->yend = ms->parms.siz.height;
 dec->tilewidth = ms->parms.siz.tilewidth;
 dec->tileheight = ms->parms.siz.tileheight;
 dec->tilexoff = ms->parms.siz.tilexoff;
 dec->tileyoff = ms->parms.siz.tileyoff;
 dec->numcomps = ms->parms.siz.numcomps;

 dec->cp = jpc_dec_cp_create(dec->numcomps);
 if (!dec->cp)
  return -1;

 dec->cmpts = jas_alloc2(dec->numcomps, sizeof(jpc_dec_cmpt_t));
 if (!dec->cmpts)
  return -1;

 for (i = 0, cmpt = dec->cmpts; i < dec->numcomps; ++i, ++cmpt) {
  cmpt->prec = ms->parms.siz.comps[i].prec;
  cmpt->sgnd = ms->parms.siz.comps[i].sgnd != 0;
  cmpt->hstep = ms->parms.siz.comps[i].hsamp;
  cmpt->vstep = ms->parms.siz.comps[i].vsamp;
  cmpt->width = ((dec->xend + cmpt->hstep - 1) / cmpt->hstep) -
   ((dec->xstart + cmpt->hstep - 1) / cmpt->hstep);
  cmpt->height = ((dec->yend + cmpt->vstep - 1) / cmpt->vstep) -
   ((dec->ystart + cmpt->vstep - 1) / cmpt->vstep);
  cmpt->hsubstep = 0;
  cmpt->vsubstep = 0;
 }

 dec->image = 0;

 dec->numhtiles = (int)(((dec->xend - dec->tilexoff) + dec->tilewidth - 1) /
  dec->tilewidth);
 dec->numvtiles = (int)(((dec->yend - dec->tileyoff) + dec->tileheight - 1) /
  dec->tileheight);
 dec->numtiles = dec->numhtiles * dec->numvtiles;

 if (jas_getdbglevel() >= 10)
  jas_eprintf("numtiles = %d; numhtiles = %d; numvtiles = %d;\n",
   dec->numtiles, dec->numhtiles, dec->numvtiles);

 dec->tiles = jas_alloc2(dec->numtiles, sizeof(jpc_dec_tile_t));
 if (!dec->tiles)
  return -1;

 for (j = 0, tile = dec->tiles; j < dec->numtiles; ++j, ++tile) {
  htileno = j % dec->numhtiles;
  vtileno = j / dec->numhtiles;
  tile->realmode = 0;
  tile->state = 0;
  tile->xstart = ((dec->tilexoff + htileno * dec->tilewidth) > (dec->xstart)) ? (dec->tilexoff + htileno * dec->tilewidth) : (dec->xstart);
  tile->ystart = ((dec->tileyoff + vtileno * dec->tileheight) > (dec->ystart)) ? (dec->tileyoff + vtileno * dec->tileheight) : (dec->ystart);
  tile->xend = ((dec->tilexoff + (htileno + 1) * dec->