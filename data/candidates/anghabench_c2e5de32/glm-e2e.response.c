int ff_rescale_rms(int a, int b) {
    return (a * b) >> 10;
}