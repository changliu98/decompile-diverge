int raid6_next_disk(int current, int max) {
    current++;
    if (current < max) {
        return current;
    } else {
        return 0;
    }
}