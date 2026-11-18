static int jpc_dec_process_siz(jpc_dec_t *dec, jpc_ms_t *ms)
{
 int compno;
 int tileno;
 int htileno;
 int vtileno;
 jpc_cparameters_t *params;
 jpc_dec_tile_t *tile;
 jpc_dec_comp_t *tcomp;
 jpc_dec_ccp_t *ccp;
 int ret;

 params = &((jpc_ms_cparameters_t *) (&ms->data[0]))->cparameters;

 dec->image_width = params->width;
 dec->image_height = params->height;
 dec->numcomps = params->numcomps;
 dec->numlayers = params->numlayers;
 dec->xref = params->xref;
 dec->yref = params->yref;
 dec->xreforig = params->xreforig;
 dec->yreforig = params->yreforig;
 dec->numcomps = params->numcomps;
 if (!(dec->cp = jpc_dec_cp_create(dec->numcomps))) {
  ret = -1;
  goto error;
 }
 if (!(dec->comps = jas_alloc2(dec->numcomps,
   sizeof(jpc_dec_comp_t)))) {
  ret = -1;
  goto error;
 }
 for (compno = 0, ccp = dec->comps; compno < dec->numcomps; ++compno,
   ++ccp) {
  if (compno >= params->numcomps) {
   break;
  }
  ccp->prec = params->comps[compno].prec;
  ccp->sgnd = ((params->comps[compno].sgnd) ? 1 : 0);
  ccp->w = params->comps[compno].w;
  ccp->h = params->comps[compno].h;
  ccp->step_x = (((((dec->numcomps) + (ccp->w) - 1) / (ccp->w)) - (((dec->image_width) + (ccp->w) - 1) / (ccp->w))));
  ccp->step_y = (((((dec->numcomps) + (ccp->h) - 1) / (ccp->h)) - (((dec->image_height) + (ccp->h) - 1) / (ccp->h))));
  ccp->numchans = 0;
  ccp->numchansbuf = 0;
 }

 dec->numhtiles = (((((dec->image_width) - (dec->xreforig)) + (dec->xref) - 1) / (dec->xref)));
 dec->numvtiles = (((((dec->image_height) - (dec->yreforig)) + (dec->yref) - 1) / (dec->yref)));
 dec->numtiles = dec->numhtiles * dec->numvtiles;
 do { if ((jas_getdbglevel() >= 11)) jas_eprintf("numtiles = %d; numhtiles = %d; numvtiles = %d\n", dec->numtiles, dec->numhtiles, dec->numvtiles); } while (0);;
 if (!(dec->tiles = jas_alloc2(dec->numtiles,
   sizeof(jpc_dec_tile_t)))) {
  ret = -1;
  goto error;
 }
 for (tileno = 0, tile = dec->tiles; tileno < dec->numtiles; ++tileno,
   ++tile) {
  htileno = tileno % dec->numhtiles;
  vtileno = tileno / dec->numhtiles;
  tile->numcompstot = 0;
  tile->numcomps = 0;
  if (htileno * dec->xref + dec->xreforig < dec->image_width) {
   tile->xref = htileno * dec->xref + dec->xreforig;
  } else {
   tile->xref = dec->image_width;
  }
  if (vtileno * dec->yref + dec->yreforig < dec->image_height) {
   tile->yref = vtileno * dec->yref + dec->yreforig;
  } else {
   tile->yref = dec->image_height;
  }
  if ((htileno + 1) * dec->xref + dec->xreforig < dec->image_width) {
   tile->xrefend = (htileno + 1) * dec->xref + dec->xreforig;
  } else {
   tile->xrefend = dec->image_width;
  }
  if ((vtileno + 1) * dec->yref + dec->yreforig < dec->image_height) {
   tile->yrefend = (vtileno + 1) * dec->yref + dec->yreforig;
  } else {
   tile->yrefend = dec->image_height;
  }
  tile->numcompstot = 0;
  tile->numcomps = 0;
  tile->numcompstot = 0;
  tile->numcomps = 0;
  tile->numcompstot = 0;
  tile->numcomps = 0;
  tile->numcompstot = 0;
  tile->numcomps = 0;
  if (!(tile->comps = jas_alloc2(dec->numcomps,
    sizeof(jpc_dec_comp_t)))) {
   ret = -1;
   goto error;
  }
  for (compno = 0, ccp = dec->comps, tcomp = tile->comps; compno <
    dec->numcomps; ++compno, ++ccp, ++tcomp) {
   tcomp->numchans = 0;
   tcomp->numchansbuf = 0;
   tcomp->numrows = 0;
   tcomp->numrowsbuf = (((((tile->xrefend) + (ccp->w) - 1) / (ccp->w)) - (((tile->xref) + (ccp->w) - 1) / (ccp->w))));
   tcomp->numcols = (((((tile->yrefend) + (ccp->h) - 1) / (ccp->h)) - (((tile->yref) + (ccp->h) - 1) / (ccp->h))));
   tcomp->numrows = (((((tile->xrefend) + (ccp->w) - 1) / (ccp->w)) - (((tile->xref) + (ccp->w) - 1) / (ccp->w))));
   tcomp->numcols = (((((tile->yrefend) + (ccp->h) - 1) / (ccp->h)) - (((tile->yref) + (ccp->h) - 1) / (ccp->h))));
   tcomp->numrowsbuf = 0;
  }
 }
 dec->numrestiles = 0;
 dec->state = 4;
 return 0;

error:
 return ret;
}