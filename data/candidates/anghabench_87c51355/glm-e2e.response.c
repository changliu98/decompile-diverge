long spc_used(long a, long b, long c) {
    int diff = a - b;
    long result;
    
    if (diff < 0) {
        result = c + diff;
    } else {
        result = diff;
    }
    
    return result;
}