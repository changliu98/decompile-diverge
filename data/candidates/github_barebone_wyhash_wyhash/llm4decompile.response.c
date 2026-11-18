uint64_t wyhash(const void *key, uint64_t len, uint64_t seed, const uint64_t *secret) {
    const uint8_t *p = (const uint8_t *)key;
    uint64_t a, b;

    seed ^= secret[0];
    a = _wymix(seed ^ secret[0], secret[1]);
    b = seed ^ a;

    if (len <= 16) {
        if (len >= 4) {
            a = (a ^ ((uint64_t)_wyr4(p) << 32 | _wyr4(p + ((len >> 3) << 3)))) ^ ((uint64_t)_wyr4(p + len - 4) << 32 | _wyr4(p + len - 4 - ((len >> 3) << 3)));
            b = (b ^ ((uint64_t)_wyr4(p + len - ((len >> 3) << 3)) << 32 | _wyr4(p + len - 4 - ((len >> 3) << 3)))) ^ ((uint64_t)_wyr4(p) << 32 | _wyr4(p + ((len >> 3) << 3)));
        } else if (len) {
            a = (a ^ ((uint64_t)_wyr3(p, len) << 32 | 0)) ^ ((uint64_t)0 << 32 | 0);
            b = (b ^ ((uint64_t)0 << 32 | 0)) ^ ((uint64_t)_wyr3(p, len) << 32 | 0);
        } else {
            a = (a ^ ((uint64_t)0 << 32 | 0)) ^ ((uint64_t)0 << 32 | 0);
            b = (b ^ ((uint64_t)0 << 32 | 0)) ^ ((uint64_t)0 << 32 | 0);
        }
    } else {
        while (len > 47) {
            a = _wymix(a ^ _wyr8(p), b ^ _wyr8(p + 8));
            b = _wymix(a ^ _wyr8(p + 16), b ^ _wyr8(p + 24));
            a = _wymix(a ^ _wyr8(p + 32), b ^ _wyr8(p + 40));
            p += 48;
            len -= 48;
        }
        while (len > 16) {
            a = _wymix(a ^ _wyr8(p), b ^ _wyr8(p + 8));
            p += 16;
            len -= 16;
        }
        a = a ^ _wyr8(p + len - 16);
        b = b ^ _wyr8(p + len - 8);
    }
    a = a ^ secret[0];
    b = b ^ secret[1];
    _wymum(&a, &b);
    return _wymix(a ^ secret[0] ^ len, b ^ secret[1]);
}