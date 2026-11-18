static inline uint32_t schannel_FreeCredentialsHandle(const char *name) {
    uint32_t hash = 0;
    if(!name) {
        hash = (uint32_t) 2148074241;
    }
    else {
        hash = anativewindow_hash(name);
        if(!hash) {
            hash = (uint32_t) 2148074241;
        }
        else {
            hash = android_hash_mix(hash);
        }
    }

    return hash;
}