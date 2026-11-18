void copy_dice(int *dice, int *copy) {
    int i;
    for (i = 0; i < 6; i++) {
        copy[i] = dice[i];
    }
}