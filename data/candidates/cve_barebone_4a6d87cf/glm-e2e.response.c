int jpc_dec_process_sod(jpc_dec_t *dec, void *marker) {
    jpc_dec_tile_t *tile = dec->tile;
    if (!tile) {
        return -1;
    }

    if (tile->num_parts == 0) {
        if (!jpc_dec_cp_isvalid(tile->cp)) {
            return -1;
        }
        if (jpc_dec_cp_prepare(tile->cp)) {
            return -1;
        }
        if (jpc_dec_tileinit(dec, tile)) {
            return -1;
        }
    }

    if (dec->streamlist) {
        tile->pkthdrstream = jpc_streamlist_remove(dec->streamlist, 0);
        if (!tile->pkthdrstream) {
            return -1;
        }
    }

    if (tile->pptstab) {
        if (!tile->pkthdrstream) {
            tile->pkthdrstream = jas_stream_memopen(0, 0);
            if (!tile->pkthdrstream) {
                return -1;
            }
        }
        long pos = jas_stream_tell(tile->pkthdrstream);
        jas_stream_seek(tile->pkthdrstream, 0, 2);
        if (jpc_pptstab_write(tile->pkthdrstream, tile->pptstab)) {
            return -1;
        }
        jas_stream_seek(tile->pkthdrstream, pos, 0);
        jpc_ppxstab_destroy(tile->pptstab);
        tile->pptstab = NULL;
    }

    if (jas_get_debug_level() >= 10) {
        jpc_dec_dump(dec);
    }

    jpc_dec_t *dec_ptr = dec;
    jas_stream_t *pkthdr;
    if (tile->pkthdrstream) {
        pkthdr = tile->pkthdrstream;
    } else {
        pkthdr = dec->stream;
    }

    if (jpc_dec_decodepkts(dec_ptr, pkthdr, dec->stream)) {
        jas_logerrorf("jpc_dec_decodepkts failed\n");
        return -1;
    }

    if (dec->max_samples > 0) {
        long rwcount = jas_stream_getrwcount(dec->stream);
        if (rwcount < dec->max_samples) {
            long diff = dec->max_samples - rwcount;
            jas_logwarnf("warning: trailing bytes %ld\n", diff);
            diff--;
            while (diff > 0) {
                if (jas_stream_getc(dec->stream) == -1) {
                    jas_logerrorf("jas_stream_getc failed\n");
                    return -1;
                }
                diff--;
            }
        } else if (rwcount > dec->max_samples) {
            jas_logwarnf("warning: too many bytes %ld\n", rwcount - dec->max_samples);
        }
    }

    if (tile->num_parts > 0 && tile->part_num == tile->num_parts - 1) {
        if (jpc_dec_tiledecode(dec, tile)) {
            return -1;
        }
        jpc_dec_tilefini(dec, tile);
    }

    dec->tile = NULL;
    tile->num_parts++;
    dec->state = 8;

    return 0;
}