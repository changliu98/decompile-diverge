int jpc_dec_process_siz(jpc_dec_t *dec,jpc_ms_t *ms)

{
  int iVar1;
  jpc_dec_cp_t *pjVar2;
  jpc_dec_cmpt_t *pjVar3;
  jpc_dec_tile_t *pjVar4;
  jpc_dec_tcomp_t *pjVar5;
  int iVar6;
  uint_fast32_t local_70;
  uint_fast32_t local_68;
  uint_fast32_t local_60;
  uint_fast32_t local_58;
  jpc_dec_cmpt_t *cmpt;
  int vtileno;
  int htileno;
  jpc_dec_tcomp_t *tcomp;
  jpc_dec_tile_t *tile;
  int tileno;
  int compno;
  jpc_siz_t *siz;
  jpc_ms_t *ms_local;
  jpc_dec_t *dec_local;
  int local_c;
  
  dec->xstart = (ms->parms).siz.xoff;
  dec->ystart = (ms->parms).siz.yoff;
  dec->xend = (ms->parms).siz.width;
  dec->yend = (ms->parms).siz.height;
  dec->tilewidth = (ms->parms).siz.tilewidth;
  dec->tileheight = (ms->parms).siz.tileheight;
  dec->tilexoff = (ms->parms).siz.tilexoff;
  dec->tileyoff = (ms->parms).siz.tileyoff;
  dec->numcomps = (int)(ms->parms).siz.numcomps;
  pjVar2 = jpc_dec_cp_create((long)dec->numcomps);
  dec->cp = pjVar2;
  if (pjVar2 == (jpc_dec_cp_t *)0x0) {
    local_c = -1;
  }
  else {
    pjVar3 = jas_alloc2((long)dec->numcomps,0x40);
    dec->cmpts = pjVar3;
    if (pjVar3 == (jpc_dec_cmpt_t *)0x0) {
      local_c = -1;
    }
    else {
      compno = 0;
      cmpt = dec->cmpts;
      for (; compno < dec->numcomps; compno = compno + 1) {
        cmpt->prec = (ulong)(ms->parms).siz.comps[compno].prec;
        cmpt->sgnd = (ms->parms).siz.comps[compno].sgnd != '\0';
        cmpt->hstep = (ulong)(ms->parms).siz.comps[compno].hsamp;
        cmpt->vstep = (ulong)(ms->parms).siz.comps[compno].vsamp;
        cmpt->width = ((dec->xend + cmpt->hstep) - 1) / cmpt->hstep -
                      ((dec->xstart + cmpt->hstep) - 1) / cmpt->hstep;
        cmpt->height = ((dec->yend + cmpt->vstep) - 1) / cmpt->vstep -
                       ((dec->ystart + cmpt->vstep) - 1) / cmpt->vstep;
        cmpt->hsubstep = 0;
        cmpt->vsubstep = 0;
        cmpt = cmpt + 1;
      }
      dec->image = (jas_image_t *)0x0;
      dec->numhtiles = (int)((((dec->xend - dec->tilexoff) + dec->tilewidth) - 1) / dec->tilewidth);
      dec->numvtiles =
           (int)((((dec->yend - dec->tileyoff) + dec->tileheight) - 1) / dec->tileheight);
      dec->numtiles = dec->numhtiles * dec->numvtiles;
      iVar1 = jas_getdbglevel();
      if (9 < iVar1) {
        jas_eprintf("numtiles = %d; numhtiles = %d; numvtiles = %d;\n",(ulong)(uint)dec->numtiles,
                    (ulong)(uint)dec->numhtiles,(ulong)(uint)dec->numvtiles);
      }
      pjVar4 = jas_alloc2((long)dec->numtiles,0x68);
      dec->tiles = pjVar4;
      if (pjVar4 == (jpc_dec_tile_t *)0x0) {
        local_c = -1;
      }
      else {
        tileno = 0;
        tile = dec->tiles;
        for (; tileno < dec->numtiles; tileno = tileno + 1) {
          iVar6 = tileno % dec->numhtiles;
          iVar1 = tileno / dec->numhtiles;
          tile->realmode = 0;
          tile->state = 0;
          if (dec->xstart < dec->tilexoff + (long)iVar6 * dec->tilewidth) {
            local_58 = dec->tilexoff + (long)iVar6 * dec->tilewidth;
          }
          else {
            local_58 = dec->xstart;
          }
          tile->xstart = local_58;
          if (dec->ystart < dec->tileyoff + (long)iVar1 * dec->tileheight) {
            local_60 = dec->tileyoff + (long)iVar1 * dec->tileheight;
          }
          else {
            local_60 = dec->ystart;
          }
          tile->ystart = local_60;
          if (dec->tilexoff + (long)(iVar6 + 1) * dec->tilewidth < dec->xend) {
            local_68 = dec->tilexoff + (long)(iVar6 + 1) * dec->tilewidth;
          }
          else {
            local_68 = dec->xend;
          }
          tile->xend = local_68;
          if (dec->tileyoff + (long)(iVar1 + 1) * dec->tileheight < dec->yend) {
            local_70 = dec->tileyoff + (long)(iVar1 + 1) * dec->tileheight;
          }
          else {
            local_70 = dec->yend;
          }
          tile->yend = local_70;
          tile->numparts = 0;
          tile->partno = 0;
          tile->pkthdrstream = (jas_stream_t *)0x0;
          tile->pkthdrstreampos = 0;
          tile->pptstab = (jpc_ppxstab_t *)0x0;
          tile->cp = (jpc_dec_cp_t *)0x0;
          tile->pi = (jpc_pi_t *)0x0;
          pjVar5 = jas_alloc2((long)dec->numcomps,0x40);
          tile->tcomps = pjVar5;
          if (pjVar5 == (jpc_dec_tcomp_t *)0x0) {
            return -1;
          }
          compno = 0;
          cmpt = dec->cmpts;
          tcomp = tile->tcomps;
          for (; compno < dec->numcomps; compno = compno + 1) {
            tcomp->rlvls = (jpc_dec_rlvl_t *)0x0;
            tcomp->numrlvls = 0;
            tcomp->data = (jas_matrix_t *)0x0;
            tcomp->xstart = ((tile->xstart + cmpt->hstep) - 1) / cmpt->hstep;
            tcomp->ystart = ((tile->ystart + cmpt->vstep) - 1) / cmpt->vstep;
            tcomp->xend = ((tile->xend + cmpt->hstep) - 1) / cmpt->hstep;
            tcomp->yend = ((tile->yend + cmpt->vstep) - 1) / cmpt->vstep;
            tcomp->tsfb = (jpc_tsfb_t *)0x0;
            cmpt = cmpt + 1;
            tcomp = tcomp + 1;
          }
          tile = tile + 1;
        }
        dec->pkthdrstreams = (jpc_streamlist_t *)0x0;
        dec->state = 4;
        local_c = 0;
      }
    }
  }
  return local_c;
}