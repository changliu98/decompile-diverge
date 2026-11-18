void encrypt(struct Data *data, struct Key *key) {
    uint64_t sum = 0x9e3779b9;
    uint64_t k0 = key->k0;
    uint64_t k1 = key->k1;
    uint64_t k2 = key->k2;
    uint64_t k3 = key->k3;
    
    uint64_t v0 = data->v0;
    uint64_t v1 = data->v1;
    
    uint64_t i = 0;
    for (i = 0; i < 32; i++) {
        sum += 0x9e3779b9;
        
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }
    
    data->v0 = v0;
    data->v1 = v1;
}