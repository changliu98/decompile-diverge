bool func0(const unsigned char *v, int n) {
    for (int i = 0; i < n; i++) {
        if ((v[i] & 1) == 0) {
            return false;
        }
    }
    return true;
}