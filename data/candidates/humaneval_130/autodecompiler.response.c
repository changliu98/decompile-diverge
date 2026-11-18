int* func0(int numOnes) {
    int *counts = (int*)malloc((numOnes+1)*sizeof(int));
    counts[0] = 1;
    if (numOnes == 0) return counts;

    counts[1] = 3;
    int i;
    for (i=2; i <= numOnes; i++) {
        if (i%2 == 0) {
            counts[i] = counts[i/2] + 1;
        } else {
            counts[i] = counts[i-1] + counts[i-2] + 1 + (i+1)/2;
        }
    }

    return counts;
}