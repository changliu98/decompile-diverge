int mwifiex_cmd_append_vsie_tlv(struct mwifiex_adapter *adapter, 
                                unsigned short vsie_mask, 
                                unsigned char **data_buf) {
    int ret_len = 0;
    int i;
    unsigned char *tlv;

    if (!data_buf || !*data_buf)
        return 0;

    for (i = 0; i < MWIFIEX_MAX_VSIE_NUM; i++) {
        struct vsie_entry *entry = (struct vsie_entry *)((unsigned char *)adapter + i * 0x104);
        
        if (entry->mask & vsie_mask) {
            tlv = *data_buf;
            
            // Set TLV header
            *(unsigned short *)tlv = TLV_TYPE_VSIE;
            *(unsigned short *)(tlv + 2) = entry->length + 2;
            
            // Copy data
            memcpy(tlv + TLV_HEADER_SIZE, entry->data, *(unsigned short *)(tlv + 2));
            
            // Update buffer pointer and total length
            *data_buf += *(unsigned short *)(tlv + 2) + TLV_HEADER_SIZE;
            ret_len += *(unsigned short *)(tlv + 2) + TLV_HEADER_SIZE;
        }
    }

    return ret_len;
}