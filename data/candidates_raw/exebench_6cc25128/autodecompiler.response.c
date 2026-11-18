void tea_encrypt (unsigned long *const v, unsigned long *const k) {
    unsigned long y=v[0], z=v[1], sum=0, n=32;

    while (n-->0) {
        sum += 0x9e3779b9;
        y += ((z<<4) + k[0]) ^ (z + sum) ^ ((z>>5) + k[1]);
        z += ((y<<4) + k[2]) ^ (y + sum) ^ ((y>>5) + k[3]);
    }

    v[0]=y; v[1]=z;
}