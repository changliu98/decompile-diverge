int __cdecl jpc_dec_process_siz(jpc_dec_t *dec, jpc_ms_t *ms)
{
  jpc_dec_cp_t *cp;
  jpc_dec_tile_t *tile;
  jpc_dec_tcomp_t *tcomp;
  jpc_dec_cmpt_t *cmpt;
  jpc_siz_t *siz;
  uint_fast32_t xstart, ystart, xend, yend;
  int tileno, htileno, vtileno, compno;

  siz = &ms->parms.siz;

  // Copy image and tile boundaries from the SIZ marker segment
  dec->xstart = siz->xoff;
  dec->ystart = siz->yoff;
  dec->xend = siz->width;
  dec->yend = siz->height;
  dec->tilewidth = siz->tilewidth;
  dec->tileheight = siz->tileheight;
  dec->tilexoff = siz->tilexoff;
  dec->tileyoff = siz->tileyoff;
  dec->numcomps = siz->numcomps;

  // Allocate coding parameters
  cp = jpc_dec_cp_create(dec->numcomps);
  dec->cp = cp;
  if (!cp)
    return -1;

  // Allocate components array (size of jpc_dec_cmpt_t is 0x40)
  cmpt = (jpc_dec_cmpt_t *)jas_alloc2(dec->numcomps, 0x40uLL);
  dec->cmpts = cmpt;
  if (!cmpt)
    return -1;

  // Initialize component properties
  for (compno = 0; compno < dec->numcomps; ++compno, ++cmpt) {
    cmpt->prec = siz->comps[compno].prec;
    cmpt->sgnd = siz->comps[compno].sgnd != 0;
    cmpt->hstep = siz->comps[compno].hsamp;
    cmpt->vstep = siz->comps[compno].vsamp;
    
    // Compute component dimensions based on subsampling steps
    cmpt->width = (cmpt->hstep + dec->xend - 1) / cmpt->hstep - (cmpt->hstep + dec->xstart - 1) / cmpt->hstep;
    cmpt->height = (cmpt->vstep + dec->yend - 1) / cmpt->vstep - (cmpt->vstep + dec->ystart - 1) / cmpt->vstep;
    cmpt->hsubstep = 0;
    cmpt->vsubstep = 0;
  }

  dec->image = NULL;

  // Calculate number of tiles horizontally and vertically
  dec->numhtiles = (dec->tilewidth + dec->xend - dec->tilexoff - 1) / dec->tilewidth;
  dec->numvtiles = (dec->tileheight + dec->yend - dec->tileyoff - 1) / dec->tileheight;
  dec->numtiles = dec->numvtiles * dec->numhtiles;

  if (jas_getdbglevel() >= 10)
    jas_eprintf(
      "numtiles = %d; numhtiles = %d; numvtiles = %d;\n",
      dec->numtiles, dec->numhtiles, dec->numvtiles);

  // Allocate tiles array (size of jpc_dec_tile_t is 0x68)
  tile = (jpc_dec_tile_t *)jas_alloc2(dec->numtiles, 0x68uLL);
  dec->tiles = tile;
  if (!tile)
    return -1;

  // Initialize each tile
  for (tileno = 0; tileno < dec->numtiles; ++tileno, ++tile) {
    htileno = tileno % dec->numhtiles;
    vtileno = tileno / dec->numhtiles;

    tile->realmode = 0;
    tile->state = 0;

    // Determine tile boundaries, clamping to image boundaries
    xstart = dec->tilewidth * htileno + dec->tilexoff;
    if (xstart < dec->xstart)
      xstart = dec->xstart;
    tile->xstart = xstart;

    ystart = dec->tileheight * vtileno + dec->tileyoff;
    if (ystart < dec->ystart)
      ystart = dec->ystart;
    tile->ystart = ystart;

    xend = dec->tilewidth * (htileno + 1) + dec->tilexoff;
    if (xend > dec->xend)
      xend = dec->xend;
    tile->xend = xend;

    yend = dec->tileheight * (vtileno + 1) + dec->tileyoff;
    if (yend > dec->yend)
      yend = dec->yend;
    tile->yend = yend;

    tile->numparts = 0;
    tile->partno = 0;
    tile->pkthdrstream = NULL;
    tile->pkthdrstreampos = NULL;
    tile->pptstab = NULL;
    tile->cp = NULL;
    tile->pi = NULL;

    // Allocate tile-components array (size of jpc_dec_tcomp_t is 0x40)
    tcomp = (jpc_dec_tcomp_t *)jas_alloc2(dec->numcomps, 0x40uLL);
    tile->tcomps = tcomp;
    if (!tcomp)
      return -1;

    cmpt = dec->cmpts;
    for (compno = 0; compno < dec->numcomps; ++compno, ++cmpt, ++tcomp) {
      tcomp->rlvls = NULL;
      tcomp->numrlvls = 0;
      tcomp->data = NULL;
      
      // Map tile boundaries to component coordinates using subsampling
      tcomp->xstart = (cmpt->hstep + tile->xstart - 1) / cmpt->hstep;
      tcomp->ystart = (cmpt->vstep + tile->ystart - 1) / cmpt->vstep;
      tcomp->xend = (cmpt->hstep + tile->xend - 1) / cmpt->hstep;
      tcomp->yend = (cmpt->vstep + tile->yend - 1) / cmpt->vstep;
      
      tcomp->tsfb = NULL;
    }
  }

  dec->pkthdrstreams = NULL;
  dec->state = 4; // JPC_DEC_MT
  return 0;
}