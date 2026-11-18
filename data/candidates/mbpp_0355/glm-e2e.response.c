int func0(int n) {
    int count = 0;
    int limit = n * 2;
    int target = limit * limit;
    
    for (int i = 1; i < limit; i++) {
        for (int j = 1; j < limit; j++) {
            int sum = i * i + j * j;
            if (sum <= target) {
                count++;
            }
        }
    }
    
    return count;
}