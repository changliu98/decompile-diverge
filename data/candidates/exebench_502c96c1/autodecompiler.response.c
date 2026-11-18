void encipher (unsigned long *const v, unsigned long *const k) {
    unsigned long y=v[0], z=v[1], sum=0, n=32, delta=0x9e3779b9;
    while (n-->0) {
        sum += delta;
        y += ((z<<4) + k[0]) ^ (z + sum) ^ ((z>>5) + k[sum&3]);
        z += ((y<<4) + k[0]) ^ (y + sum) ^ ((y>>5) + k[(sum>>11)&3]);
    }
    v[0]=y; v[1]=z;
}