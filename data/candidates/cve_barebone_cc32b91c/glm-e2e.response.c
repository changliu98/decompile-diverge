int rx_cache_find(void *p, void *opaque, int length, uint32_t *result) {
    uint32_t serviceId = *(uint32_t *)((char *)opaque + 0x10);
    uint32_t epoch = *(uint32_t *)((char *)opaque + 0x0c);
    int hint = rx_cache_hint;
    
    do {
        struct rx_cache_entry *entry = &rx_cache[hint];
        
        if (entry->field_0 == EXTRACT_32BITS((char *)p + 8) &&
            entry->field_4 == serviceId &&
            entry->field_8 == epoch &&
            entry->field_10 == EXTRACT_32BITS((char *)p + 0x1a) &&
            entry->field_c == length) {
            
            rx_cache_hint = hint;
            *result = entry->field_14;
            return 1;
        }
        
        hint++;
        if (hint >= 64) {
            hint = 0;
        }
    } while (hint != rx_cache_hint);
    
    return 0;
}