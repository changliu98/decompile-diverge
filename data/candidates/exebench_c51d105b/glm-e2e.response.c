void png_64bit_product(int a, int b, unsigned int *hi, unsigned int *lo) {
    int a_hi = (a >> 16) & 0xffff;
    int a_lo = a & 0xffff;
    int b_hi = (b >> 16) & 0xffff;
    int b_lo = b & 0xffff;

    long long ll = (long long)a_lo * b_lo;
    long long mid = (long long)(a_hi * b_lo + a_lo * b_hi);
    
    long long sum = mid + ((ll >> 16) & 0xffff);
    
    ll = (ll & 0xffff) | ((sum & 0xffff) << 16);
    
    long long high = (sum >> 16) & 0xffff;
    high += (long long)a_hi * b_hi;

    *hi = (unsigned int)high;
    *lo = (unsigned int)ll;
}