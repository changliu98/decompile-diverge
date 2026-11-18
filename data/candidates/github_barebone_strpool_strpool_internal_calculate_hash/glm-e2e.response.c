uint32_t strpool_internal_calculate_hash(const char *string, int length, int ignore_case) {
    uint32_t hash = 5381; // 0x1505

    if (ignore_case) {
        for (int i = 0; i < length; ++i) {
            char c = string[i];
            if (c >= 'a' && c <= 'z') {
                c -= 0x20; // Convert to uppercase
            }
            hash = ((hash << 5) + hash) ^ c;
        }
    } else {
        for (int i = 0; i < length; ++i) {
            char c = string[i];
            hash = ((hash << 5) + hash) ^ c;
        }
    }

    if (hash == 0) {
        hash = 1;
    }

    return hash;
}