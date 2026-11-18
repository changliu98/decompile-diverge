struct RebaseInfos *get_rebase_infos(struct SomeStruct *bin) {
    struct RebaseInfos *rebase_infos = calloc(1, 0x10);
    if (!rebase_infos) {
        return NULL;
    }

    if (bin->s2->field_0x38 == 0 || bin->s2->field_0x40 == 0) {
        ut32 count = 0;
        ut32 sizes[16];
        for (ut32 i = 0; i < bin->nsegs && i < 16; i++) {
            struct RzBinElfSeg *seg = bin->segs[i];
            if (!rz_buf_read_le32_at(bin->buf, seg + 0x13c, &sizes[i])) {
                goto fail;
            }
            count += sizes[i];
        }

        if (count == 0) {
            goto fail;
        }

        struct RebaseInfo *infos = calloc(count, 0x18);
        if (!infos) {
            goto fail;
        }

        ut32 idx = 0;
        for (ut32 i = 0; i < bin->nsegs && i < 16; i++) {
            struct RzBinElfSeg *seg = bin->segs[i];
            if (sizes[i] == 0) {
                continue;
            }

            ut32 nentries;
            if (!rz_buf_read_le32_at(bin->buf, seg + 0x138, &nentries)) {
                continue;
            }

            if (nentries == 0) {
                continue;
            }

            ut64 base = seg + nentries;
            struct RebaseInfo *prev = NULL;

            for (ut32 j = 0; j < sizes[i]; j++) {
                struct {
                    ut64 field_0x0;
                    ut64 field_0x8;
                    ut64 field_0x10;
                    ut64 field_0x18;
                    ut64 field_0x20;
                    ut64 field_0x28;
                    ut64 field_0x30;
                } entry;

                if (rz_buf_fread_at(bin->buf, base + j * 0x38, &entry, "7q", 1) != 0x38) {
                    break;
                }

                if (entry.field_0x10 == 0 || entry.field_0x8 == 0) {
                    continue;
                }

                infos[idx].offset = entry.field_0x18 + seg;
                infos[idx].size = entry.field_0x0 + infos[idx].offset;
                infos[idx].info = get_rebase_info(bin, entry.field_0x10 + seg, entry.field_0x8, entry.field_0x18 + seg, prev ? prev->info : (ut64)-1);
                prev = &infos[idx];
                idx++;
            }
        }

        if (idx == 0) {
            free(infos);
            goto fail;
        }

        if (idx < count) {
            struct RebaseInfo *new_infos = calloc(idx, 0x18);
            if (!new_infos) {
                free(infos);
                goto fail;
            }
            memcpy(new_infos, infos, idx * 0x18);
            free(infos);
            infos = new_infos;
        }

        rebase_infos->infos = infos;
        rebase_infos->count = idx;
        return rebase_infos;
    } else {
        if (bin->s2->field_0x14 <= 1) {
            goto fail;
        }

        struct RebaseInfo *info = calloc(1, 0x18);
        if (!info) {
            goto fail;
        }

        info->offset = bin->s3->field_0x30;
        info->size = info->offset + bin->s3->field_0x28;
        info->info = get_rebase_info(bin, bin->s2->field_0x38, bin->s2->field_0x40, info->offset, (ut64)-1);

        rebase_infos->infos = info;
        rebase_infos->count = 1;
        return rebase_infos;
    }

fail:
    free(rebase_infos);
    return NULL;
}