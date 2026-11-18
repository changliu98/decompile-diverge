int __cdecl jpc_dec_process_siz(jpc_dec_t *dec, jpc_ms_t *ms)
{
  jpc_dec_cp_t *v2; // rax
  jpc_dec_cmpt_t *v3; // rax
  jpc_dec_tile_t *v4; // rax
  jpc_dec_tcomp_t *v5; // rax
  uint_fast32_t yend; // [rsp+8h] [rbp-68h]
  uint_fast32_t xend; // [rsp+10h] [rbp-60h]
  uint_fast32_t ystart; // [rsp+18h] [rbp-58h]
  uint_fast32_t xstart; // [rsp+20h] [rbp-50h]
  jpc_dec_cmpt_t *cmpt; // [rsp+28h] [rbp-48h]
  jpc_dec_cmpt_t *cmpta; // [rsp+28h] [rbp-48h]
  int vtileno; // [rsp+30h] [rbp-40h]
  int htileno; // [rsp+34h] [rbp-3Ch]
  jpc_dec_tcomp_t *tcomp; // [rsp+38h] [rbp-38h]
  jpc_dec_tile_t *tile; // [rsp+40h] [rbp-30h]
  int tileno; // [rsp+48h] [rbp-28h]
  int compno; // [rsp+4Ch] [rbp-24h]
  int compnoa; // [rsp+4Ch] [rbp-24h]

  *(_OWORD *)&dec->xstart = *(_OWORD *)&ms->parms.siz.xoff;
  *(_OWORD *)&dec->xend = *(_OWORD *)&ms->parms.siz.width;
  *(_OWORD *)&dec->tilewidth = *(_OWORD *)&ms->parms.siz.tilewidth;
  *(_OWORD *)&dec->tilexoff = *(_OWORD *)&ms->parms.siz.tilexoff;
  dec->numcomps = ms->parms.siz.numcomps;
  v2 = jpc_dec_cp_create(dec->numcomps);
  dec->cp = v2;
  if ( !v2 )
    return -1;
  v3 = (jpc_dec_cmpt_t *)jas_alloc2(dec->numcomps, 0x40uLL);
  dec->cmpts = v3;
  if ( !v3 )
    return -1;
  compno = 0;
  cmpt = dec->cmpts;
  while ( compno < dec->numcomps )
  {
    cmpt->prec = ms->parms.siz.comps[compno].prec;
    cmpt->sgnd = ms->parms.siz.comps[compno].sgnd != 0;
    cmpt->hstep = ms->parms.siz.comps[compno].hsamp;
    cmpt->vstep = ms->parms.siz.comps[compno].vsamp;
    cmpt->width = (cmpt->hstep + dec->xend - 1) / cmpt->hstep - (cmpt->hstep + dec->xstart - 1) / cmpt->hstep;
    cmpt->height = (cmpt->vstep + dec->yend - 1) / cmpt->vstep - (cmpt->vstep + dec->ystart - 1) / cmpt->vstep;
    cmpt->hsubstep = 0LL;
    cmpt->vsubstep = 0LL;
    ++compno;
    ++cmpt;
  }
  dec->image = 0LL;
  dec->numhtiles = (dec->tilewidth + dec->xend - dec->tilexoff - 1) / dec->tilewidth;
  dec->numvtiles = (dec->tileheight + dec->yend - dec->tileyoff - 1) / dec->tileheight;
  dec->numtiles = dec->numvtiles * dec->numhtiles;
  if ( jas_getdbglevel() >= 10 )
    jas_eprintf(
      "numtiles = %d; numhtiles = %d; numvtiles = %d;\n",
      (unsigned int)dec->numtiles,
      (unsigned int)dec->numhtiles,
      (unsigned int)dec->numvtiles);
  v4 = (jpc_dec_tile_t *)jas_alloc2(dec->numtiles, 0x68uLL);
  dec->tiles = v4;
  if ( !v4 )
    return -1;
  tileno = 0;
  tile = dec->tiles;
  while ( tileno < dec->numtiles )
  {
    htileno = tileno % dec->numhtiles;
    vtileno = tileno / dec->numhtiles;
    tile->realmode = 0;
    tile->state = 0;
    if ( dec->tilewidth * htileno + dec->tilexoff <= dec->xstart )
      xstart = dec->xstart;
    else
      xstart = dec->tilewidth * htileno + dec->tilexoff;
    tile->xstart = xstart;
    if ( dec->tileheight * vtileno + dec->tileyoff <= dec->ystart )
      ystart = dec->ystart;
    else
      ystart = dec->tileheight * vtileno + dec->tileyoff;
    tile->ystart = ystart;
    if ( dec->tilewidth * (htileno + 1) + dec->tilexoff >= dec->xend )
      xend = dec->xend;
    else
      xend = dec->tilewidth * (htileno + 1) + dec->tilexoff;
    tile->xend = xend;
    if ( dec->tileheight * (vtileno + 1) + dec->tileyoff >= dec->yend )
      yend = dec->yend;
    else
      yend = dec->tileheight * (vtileno + 1) + dec->tileyoff;
    tile->yend = yend;
    tile->numparts = 0;
    tile->partno = 0;
    tile->pkthdrstream = 0LL;
    tile->pkthdrstreampos = 0LL;
    tile->pptstab = 0LL;
    tile->cp = 0LL;
    tile->pi = 0LL;
    v5 = (jpc_dec_tcomp_t *)jas_alloc2(dec->numcomps, 0x40uLL);
    tile->tcomps = v5;
    if ( !v5 )
      return -1;
    compnoa = 0;
    cmpta = dec->cmpts;
    tcomp = tile->tcomps;
    while ( compnoa < dec->numcomps )
    {
      tcomp->rlvls = 0LL;
      tcomp->numrlvls = 0;
      tcomp->data = 0LL;
      tcomp->xstart = (cmpta->hstep + tile->xstart - 1) / cmpta->hstep;
      tcomp->ystart = (cmpta->vstep + tile->ystart - 1) / cmpta->vstep;
      tcomp->xend = (cmpta->hstep + tile->xend - 1) / cmpta->hstep;
      tcomp->yend = (cmpta->vstep + tile->yend - 1) / cmpta->vstep;
      tcomp->tsfb = 0LL;
      ++compnoa;
      ++cmpta;
      ++tcomp;
    }
    ++tileno;
    ++tile;
  }
  dec->pkthdrstreams = 0LL;
  dec->state = 4;
  return 0;
}