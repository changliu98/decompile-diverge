void func0(int* game, int* guess, int* out, int length) {
    for (int i = 0; i < length; i++) {
        out[i] = abs(game[i] - guess[i]);
    }
}