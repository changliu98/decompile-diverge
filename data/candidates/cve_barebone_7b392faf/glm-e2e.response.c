int xid_map_enter(void *arg1, const uint8_t *arg2, const uint8_t *arg3) {
    struct xid_map_entry *entry;
    const uint8_t *v4 = NULL;
    const uint8_t *v5 = NULL;

    uint64_t capacity = *(uint64_t *)((char *)arg1 + 8);
    if ((uint64_t)(&arg2[16] - 4) > capacity) {
        return 0;
    }

    uint8_t type = (*arg3 >> 4) & 0xF;
    if (type == 4) {
        v4 = arg3;
    } else if (type == 6) {
        v5 = arg3;
    } else {
        return 1;
    }

    entry = &xid_map[xid_map_next];
    xid_map_next++;
    if (xid_map_next < 64) {
        xid_map_next = 0;
    }

    entry->field_0 = *(uint32_t *)arg2;

    if (v4 != NULL) {
        entry->field_4 = 4;
        entry->field_8 = *(uint32_t *)(v4 + 12);
        entry->field_24 = *(uint32_t *)(v4 + 16);
    } else if (v5 != NULL) {
        entry->field_4 = 6;
        entry->field_8 = *(uint32_t *)(v5 + 8);
        entry->field_16 = *(uint32_t *)(v5 + 16);
        entry->field_24 = *(uint32_t *)(v5 + 24);
        entry->field_32 = *(uint32_t *)(v5 + 32);
    }

    entry->field_40 = EXTRACT_32BITS(arg2 + 20);
    entry->field_44 = EXTRACT_32BITS(arg2 + 16);

    return 1;
}