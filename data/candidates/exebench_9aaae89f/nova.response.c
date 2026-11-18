static void pick(int *deg, int *dir) {
    *dir += 1;
    if (*dir >= 768) {
        *deg += 1;
        *dir = 0;
    }
    if (*deg >= 180)
        *deg = 0;
}