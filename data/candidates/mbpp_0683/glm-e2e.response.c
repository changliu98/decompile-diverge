bool func0(int n) {
    bool found = false;
    for (int i = 1; i * i <= n; i++) {
        for (int j = 1; j * j <= n; j++) {
            if (i * i + j * j == n) {
                found = true;
                goto done;
            }
        }
    }
    found = false;
done:
    return found;
}