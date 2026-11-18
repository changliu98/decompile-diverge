The main hash function
uint64_t wyhash(const void *key, uint64_t len, uint64_t seed, const uint64_t *secret) {
    const uint8_t *p = (const uint8_t *)key;
    uint64_t a, b;

    // Initial seed mixing
    seed ^= _wymix(seed ^ secret[0], secret[1]);

    if (len <= 16) {
        if (len >= 4) {
            // Read two 4-byte blocks to form a 64-bit value
            a = ((uint64_t)_wyr4(p) << 32) | _wyr4(p + (len >> 3) * 4);
            // Read the last 4 bytes, adjusting for overlap
            b = ((uint64_t)_wyr4(p + len - 4) << 32) | _wyr4(p + len - 4 - (len >> 3) * 4);
        } else if (len > 0) {
            a = _wyr3(p, len);
            b = 0;
        } else {
            a = 0;
            b = 0;
        }
    } else {
        uint64_t i = len;
        
        // Process chunks of 48 bytes
        if (i > 48) {
            uint64_t see1 = seed;
            uint64_t see2 = seed;
            do {
                seed = _wymix(_wyr8(p) ^ secret[1], _wyr8(p + 8) ^ seed);
                see1 = _wymix(_wyr8(p + 16) ^ secret[2], _wyr8(p + 24) ^ see1);
                see2 = _wymix(_wyr8(p + 32) ^ secret[3], _wyr8(p + 40) ^ see2);
                p += 48;
                i -= 48;
            } while (i > 48);
            seed ^= see1 ^ see2;
        }
        
        // Process chunks of 16 bytes
        while (i > 16) {
            seed = _wymix(_wyr8(p) ^ secret[1], _wyr8(p + 8) ^ seed);
            p += 16;
            i -= 16;
        }
        
        // Handle the remaining 1 to 16 bytes
        a = _wyr8(p + i - 16);
        b = _wyr8(p + i - 8);
    }

    // Final mixing and multiplication
    a ^= secret[1];
    b ^= seed;
    _wymum(&a, &b);
    return _wymix(a ^ secret[0] ^ len, b ^ secret[1]);
}