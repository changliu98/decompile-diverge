int jpc_dec_process_siz(struct jpc_dec *dec, struct jpc_ms *ms)
{
  struct jpc_dec_cmpt *cmpt;
  struct jpc_dec_tile *tile;
  struct jpc_dec_tcomp *tcomp;
  int compno;
  int tileno;
  int htileno;
  int vtileno;
  unsigned int xstart;
  unsigned int ystart;
  unsigned int xend;
  unsigned int yend;
  dec->xstart = ms->parms.siz.xoff;
  dec->xend = ms->parms.siz.width;
  dec->tilewidth = ms->parms.siz.tilewidth;
  dec->tilexoff = ms->parms.siz.tilexoff;
  dec->numcomps = ms->parms.siz.numcomps;
  if ((dec->cp = jpc_dec_cp_new(dec->numcomps)) == ((void *)0))
    return -1;
  if ((dec->cmpts = jpc_dec_cmpt_new(dec->numcomps, sizeof(jpc_dec_cmpt))) == ((void *)0))
    return -1;
  for (compno = 0, cmpt = dec->cmpts; compno < dec->numcomps; compno++, cmpt++) {
    cmpt->prec = ms->parms.siz.comps[compno].prec;
    cmpt->sgnd = (ms->parms.siz.comps[compno].sgnd == 0) ? 0 : 1;
    cmpt->hstep = ms->parms.siz.comps[compno].hsamp;
    cmpt->vstep = ms->parms.siz.comps[compno].vsamp;
    cmpt->width = ((cmpt->hstep + dec->xend - 1) / cmpt->hstep) - ((cmpt->hstep + dec->xstart - 1) / cmpt->hstep);
    cmpt->height = ((cmpt->vstep + dec->yend - 1) / cmpt->vstep) - ((cmpt->vstep + dec->ystart - 1) / cmpt->vstep);
    cmpt->hsubstep = 0;
    cmpt->vsubstep = 0;
  }
  dec->image = ((void *)0);
  dec->numhtiles = ((dec->xend - dec->tilexoff + dec->tilewidth - 1) / dec->tilewidth);
  dec->numvtiles = ((dec->yend - dec->tileyoff + dec->tileheight - 1) / dec->tileheight);
  dec->numtiles = dec->numhtiles * dec->numvtiles;
  if (jpc_log_get_level() >= jpc_log_level_info)
    jpc_log_log(jpc_log_module_dec, jpc_log_level_info, "numtiles = %d; numhtiles = %d; numvtiles = %d;\n", dec->numtiles, dec->numhtiles, dec->numvtiles);
  if ((dec->tiles = jpc_dec_tile_new(dec->numtiles, sizeof(jpc_dec_tile))) == ((void *)0))
    return -1;
  for (tileno = 0, tile = dec->tiles; tileno < dec->numtiles; tileno++, tile++) {
    htileno = tileno % dec->numhtiles;
    vtileno = tileno / dec->numhtiles;
    tile->realmode = 0;
    tile->state = 0;
    if (tile->xstart = (dec->tilexoff + (dec->tilewidth * htileno)) > dec->xstart)
      tile->xstart = (dec->tilexoff + (dec->tilewidth * htileno));
    else
      tile->xstart = dec->xstart;
    if (tile->ystart = (dec->tileyoff + (dec->tileheight * vtileno)) > dec->ystart)
      tile->ystart = (dec->tileyoff + (dec->tileheight * vtileno));
    else
      tile->ystart = dec->ystart;
    if (tile->xend = (dec->tilexoff + (dec->tilewidth * (htileno + 1))) < dec->xend)
      tile->xend = (dec->tilexoff + (dec->tilewidth * (htileno + 1)));
    else
      tile->xend = dec->xend;
    if (tile->yend = (dec->tileyoff + (dec->tileheight * (vtileno + 1))) < dec->yend)
      tile->yend = (dec->tileyoff + (dec->tileheight * (vtileno + 1)));
    else
      tile->yend = dec->yend;
    tile->numparts = 0;
    tile->partno = 0;
    tile->pkthdrstream = ((void *)0);
    tile->pkthdrstreampos = 0;
    tile->pptstab = ((void *)0);
    tile->cp = ((void *)0);
    tile->pi = ((void *)0);
    if ((tile->tcomps = jpc_dec_tcomp_new(dec->numcomps, sizeof(jpc_dec_tcomp))) == ((void *)0))
      return -1;
    for (compno = 0, cmpt = dec->cmpts, tcomp = tile->tcomps; compno < dec->numcomps; compno++, cmpt++, tcomp++) {
      tcomp->rlvls = ((void *)0);
      tcomp->numrlvls = 0;
      tcomp->data = ((void *)0);
      tcomp->xstart = ((cmpt->hstep + tile->xstart - 1) / cmpt->hstep);
      tcomp->ystart = ((cmpt->vstep + tile->ystart - 1) / cmpt->vstep);
      tcomp->xend = ((cmpt->hstep + tile->xend - 1) / cmpt->hstep);
      tcomp->yend = ((cmpt->vstep + tile->yend - 1) / cmpt->vstep);
      tcomp->tsfb = ((void *)0);
    }
  }
  dec->pkthdrstreams = ((void *)0);
  dec->state = jpc_dec_state_get;
  return 0;
}