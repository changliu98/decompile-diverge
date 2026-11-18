int store_update(struct update_header *header, struct update_data *update) {
    struct XDR xdr;
    int status = 0;
    
    struct update_header *h = header->data_ptr;
    int block_size = header->field_10;
    
    unsigned long xdr_size = xdr_sizeof(xdr_kdb_incr_update_t, update);
    int required_size = (int)(xdr_size + 0x1c);
    
    if ((unsigned int)required_size > h->rec_size) {
        int ret = resize(header, block_size, header->field_14, required_size);
        if (ret != 0) {
            return ret;
        }
    }
    
    h->field_24 = 2;
    
    int index = (update->size - 1) % block_size;
    char *record = h->records + (long long)index * h->rec_size;
    
    memset(record, 0, h->rec_size);
    
    *(int *)record = 0x06661212;
    *(int *)(record + 0x14) = (int)xdr_size;
    *(int *)(record + 0x4) = update->size;
    *(long long *)(record + 0x8) = update->field_14;
    *(int *)(record + 0x10) = 0;
    
    xdrmem_create(&xdr, record + 0x18, (int)xdr_size, XDR_ENCODE);
    if (!xdr_kdb_incr_update_t(&xdr, update)) {
        return 0x95e4fafe;
    }
    
    *(int *)(record + 0x10) = 1;
    sync_update(h, record);
    
    h->field_20 = update->size;
    h->field_14 = update->field_14;
    
    if (h->field_8 == 0) {
        h->field_8 = 1;
        h->field_1c = update->size;
        h->field_c = update->field_14;
    } else {
        if ((unsigned int)h->field_8 < (unsigned int)block_size) {
            h->field_8++;
        } else {
            int old_index = update->size % block_size;
            char *old_record = h->records + (long long)old_index * h->rec_size;
            h->field_1c = *(int *)(old_record + 0x4);
            h->field_c = *(long long *)(old_record + 0x8);
        }
    }
    
    h->field_24 = 1;
    sync_header(h);
    
    return 0;
}