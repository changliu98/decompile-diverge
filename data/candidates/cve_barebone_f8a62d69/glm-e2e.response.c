int jpc_dec_process_siz(jpc_dec_t *dec, jpc_siz_t *siz) {
    jpc_dec_cmpt_t *cmpt;
    jpc_dec_tile_t *tile;
    jpc_dec_cp_t *cp;
    int i;
    int j;
    int tileno;
    int htileno;
    int vtileno;
    uint32_t xstart;
    uint32_t ystart;
    uint32_t xend;
    uint32_t yend;

    dec->width = siz->width;
    dec->height = siz->height;
    dec->tilewidth = siz->tilewidth;
    dec->tileheight = siz->tileheight;
    dec->tilexoff = siz->tilexoff;
    dec->tileyoff = siz->tileyoff;
    dec->xoff = siz->xoff;
    dec->yoff = siz->yoff;
    dec->numcmpts = siz->numcmpts;

    if (!(dec->cp = jpc_dec_cp_create(dec->numcmpts))) {
        return -1;
    }

    if (!(dec->cmpts = jas_alloc2(dec->numcmpts, sizeof(jpc_dec_cmpt_t)))) {
        return -1;
    }

    for (i = 0, cmpt = dec->cmpts; i < dec->numcmpts; ++i, ++cmpt) {
        cmpt->sgnd = siz->cmpts[i].sgnd;
        cmpt->prec = siz->cmpts[i].prec;
        cmpt->hstep = siz->cmpts[i].hsamp;
        cmpt->vstep = siz->cmpts[i].vsamp;
        cmpt->hsub = (dec->width + cmpt->hstep - 1) / cmpt->hstep - (dec->xoff + cmpt->hstep - 1) / cmpt->hstep;
        cmpt->vsub = (dec->height + cmpt->vstep - 1) / cmpt->vstep - (dec->yoff + cmpt->vstep - 1) / cmpt->vstep;
        cmpt->unk_30 = 0;
        cmpt->unk_38 = 0;
    }

    dec->unk_00 = 0;
    dec->numhtiles = (dec->tilewidth + dec->xoff - 1) / dec->tilewidth;
    dec->numvtiles = (dec->tileheight + dec->yoff - 1) / dec->tileheight;
    dec->numhtiles = dec->numhtiles * dec->numvtiles; // Note: assembly overwrites 0x48 with product

    if (jas_getdbglevel() >= 10) {
        jas_eprintf("numhtiles=%d; numvtiles=%d; numtiles=%d\n", dec->numhtiles, dec->numvtiles, dec->numhtiles);
    }

    if (!(dec->tiles = jas_alloc2(dec->numhtiles, sizeof(jpc_dec_tile_t)))) {
        return -1;
    }

    for (tileno = 0, tile = dec->tiles; tileno < dec->numhtiles; ++tileno, ++tile) {
        htileno = tileno % dec->numhtiles;
        vtileno = tileno / dec->numhtiles;

        tile->unk_58 = 0;
        tile->unk_00 = 0;

        xstart = dec->xoff + htileno * dec->tilewidth;
        if (xstart > dec->width) {
            xstart = dec->width;
        }
        tile->xstart = (void *)xstart;

        ystart = dec->yoff + vtileno * dec->tileheight;
        if (ystart > dec->height) {
            ystart = dec->height;
        }
        tile->ystart = (void *)ystart;

        xend = xstart + dec->tilewidth;
        if (xend > dec->width) {
            xend = dec->width;
        }
        tile->xend = (void *)xend;

        yend = ystart + dec->tileheight;
        if (yend > dec->height) {
            yend = dec->height;
        }
        tile->yend = (void *)yend;

        tile->unk_54 = 0;
        tile->unk_50 = 0;
        tile->unk_30 = 0;
        tile->unk_38 = 0;
        tile->unk_28 = 0;
        tile->unk_40 = 0;
        tile->unk_60 = 0;

        if (!(tile->cmpts = jas_alloc2(dec->numcmpts, sizeof(jpc_dec_cmpt_t)))) {
            return -1;
        }

        for (i = 0, cmpt = dec->cmpts, tile->cmpts; i < dec->numcmpts; ++i, ++cmpt, ++tile->cmpts) {
            tile->cmpts->unk_30 = 0;
            tile->cmpts->unk_28 = 0;
            tile->cmpts->unk_20 = 0;
            tile->cmpts->hstep = (tile->xstart + cmpt->hstep - 1) / cmpt->hstep;
            tile->cmpts->vstep = (tile->ystart + cmpt->vstep - 1) / cmpt->vstep;
            tile->cmpts->hsub = (tile->xend + cmpt->hstep - 1) / cmpt->hstep;
            tile->cmpts->vsub = (tile->yend + cmpt->vstep - 1) / cmpt->vstep;
            tile->cmpts->unk_38 = 0;
        }
    }

    dec->unk_a8 = 0;
    dec->unk_90 = 4;
    return 0;
}