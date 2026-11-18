int func0(int n) {
    int totalPairs = (n + 1) / 2;
    int powerOf2, nextN;
    for (powerOf2 = 2; powerOf2 <= n + 1; powerOf2 <<= 1) {
        nextN = (n + 1) / powerOf2;
        totalPairs += (nextN / 2) * powerOf2;
        if (nextN % 2) {
            totalPairs += (n + 1) % powerOf2;
        }
    }
    return totalPairs;
}