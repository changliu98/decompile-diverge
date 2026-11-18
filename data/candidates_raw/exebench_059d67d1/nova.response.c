void func0(long int s, int *h, int *m, int *sec) {
    *h = s / (60 * 60);
    *m = (s / 60) % 60;
    *sec = s % 60;
}