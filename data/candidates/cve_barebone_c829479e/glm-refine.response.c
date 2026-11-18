20

GF_Err __cdecl abst_box_read(GF_Box *s, GF_BitStream *bs)
{
    GF_AdobeBootstrapInfoBox *ptr = (GF_AdobeBootstrapInfoBox *)s;
    GF_Err e;
    int i, j;
    u8 u8_val;
    char *tmp_str;
    u32 tmp_strsize;
    GF_AdobeFragmentRunTableBox *afrt = NULL;
    GF_AdobeSegmentRunTableBox *asrt = NULL;

    if (s->size < 25)
        return GF_ISOM_INVALID_FILE;

    ptr->size -= 25;
    ptr->bootstrapinfo_version = gf_bs_read_u32(bs);
    ptr->profile = gf_bs_read_int(bs, 2);
    ptr->live = gf_bs_read_int(bs, 1);
    ptr->update = gf_bs_read_int(bs, 1);
    ptr->reserved = gf_bs_read_int(bs, 4);
    ptr->time_scale = gf_bs_read_u32(bs);
    ptr->current_media_time = gf_bs_read_u64(bs);
    ptr->smpte_time_code_offset = gf_bs_read_u64(bs);

    if (ptr->size < 8)
        return GF_ISOM_INVALID_FILE;

    tmp_strsize = ptr->size;
    tmp_str = (char *)gf_malloc(tmp_strsize);
    if (!tmp_str)
        return GF_OUT_OF_MEM;
    memset(tmp_str, 0, tmp_strsize);

    // Parse movie_identifier
    i = 0;
    while (tmp_strsize) {
        if (!ptr->size) {
            gf_free(tmp_str);
            return GF_ISOM_INVALID_FILE;
        }
        --ptr->size;
        tmp_str[i] = gf_bs_read_u8(bs);
        --tmp_strsize;
        if (!tmp_str[i]) break;
        ++i;
    }
    if (i)
        ptr->movie_identifier = gf_strdup(tmp_str);

    // Parse server_entry_table
    if (!ptr->size) {
        gf_free(tmp_str);
        return GF_ISOM_INVALID_FILE;
    }
    --ptr->size;
    ptr->server_entry_count = gf_bs_read_u8(bs);
    for (i = 0; i < ptr->server_entry_count; ++i) {
        j = 0;
        tmp_strsize = ptr->size;
        while (tmp_strsize) {
            if (!ptr->size) {
                gf_free(tmp_str);
                return GF_ISOM_INVALID_FILE;
            }
            --ptr->size;
            tmp_str[j] = gf_bs_read_u8(bs);
            --tmp_strsize;
            if (!tmp_str[j]) break;
            ++j;
        }
        if (j) {
            char *entry = gf_strdup(tmp_str);
            des_setkey_enc_wrap(ptr->server_entry_table, entry, i);
        }
    }

    // Parse quality_entry_table
    if (!ptr->size) {
        gf_free(tmp_str);
        return GF_ISOM_INVALID_FILE;
    }
    --ptr->size;
    ptr->quality_entry_count = gf_bs_read_u8(bs);
    for (i = 0; i < ptr->quality_entry_count; ++i) {
        j = 0;
        tmp_strsize = ptr->size;
        while (tmp_strsize) {
            if (!ptr->size) {
                gf_free(tmp_str);
                return GF_ISOM_INVALID_FILE;
            }
            --ptr->size;
            tmp_str[j] = gf_bs_read_u8(bs);
            --tmp_strsize;
            if (!tmp_str[j]) break;
            ++j;
        }
        if (j) {
            char *entry = gf_strdup(tmp_str);
            des_setkey_enc_wrap(ptr->quality_entry_table, entry, i);
        }
    }

    // Parse drm_data
    i = 0;
    tmp_strsize = ptr->size;
    while (tmp_strsize) {
        if (!ptr->size) {
            gf_free(tmp_str);
            return GF_ISOM_INVALID_FILE;
        }
        --ptr->size;
        tmp_str[i] = gf_bs_read_u8(bs);
        --tmp_strsize;
        if (!tmp_str[i]) break;
        ++i;
    }
    if (i)
        ptr->drm_data = gf_strdup(tmp_str);

    // Parse meta_data
    i = 0;
    tmp_strsize = ptr->size;
    while (tmp_strsize) {
        if (!ptr->size) {
            gf_free(tmp_str);
            return GF_ISOM_INVALID_FILE;
        }
        --ptr->size;
        tmp_str[i] = gf_bs_read_u8(bs);
        --tmp_strsize;
        if (!tmp_str[i]) break;
        ++i;
    }
    if (i)
        ptr->meta_data = gf_strdup(tmp_str);

    // Parse segment_run_table_entries
    if (!ptr->size) {
        gf_free(tmp_str);
        return GF_ISOM_INVALID_FILE;
    }
    --ptr->size;
    ptr->segment_run_table_count = gf_bs_read_u8(bs);
    for (i = 0; i < ptr->segment_run_table_count; ++i) {
        asrt = NULL;
        e = gf_isom_box_parse((GF_Box **)&asrt, bs);
        if (e) {
            if (asrt)
                QScopedPointerPodDeleter::cleanup((GF_Box *)asrt);
            gf_free(tmp_str);
            return e;
        }
        gf_list_add(ptr->segment_run_table_entries, asrt);
    }

    // Parse fragment_run_table_entries
    if (!ptr->size) {
        gf_free(tmp_str);
        return GF_ISOM_INVALID_FILE;
    }
    --ptr->size;
    u8_val = gf_bs_read_u8(bs);
    ptr->fragment_run_table_count = u8_val;
    
    for (i = 0; i < ptr->fragment_run_table_count; ++i) {
        afrt = NULL;
        e = gf_isom_box_parse((GF_Box **)&afrt, bs);
        if (e) {
            if (afrt)
                QScopedPointerPodDeleter::cleanup((GF_Box *)afrt);
            gf_free(tmp_str);
            return e;
        }
        gf_list_add(ptr->fragment_run_table_entries, afrt);
    }

    gf_free(tmp_str);
    return GF_OK;
}