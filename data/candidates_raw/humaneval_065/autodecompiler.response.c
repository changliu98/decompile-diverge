char* rotate(int x, int num_rotations) {
    char temp[20];
    char temp2[20];
    int i;
    int j;

    sprintf(func0_xs, "%d", x);

    int len = strlen(func0_xs);
    if (len < num_rotations) {
        for (i = 0; i < len / 2; i++) {
            j = func0_xs[i];
            func0_xs[i] = func0_xs[len - 1 - i];
            func0_xs[len - 1 - i] = j;
        }
    } else {
        strcpy(temp, &func0_xs[len - num_rotations]);
        temp[num_rotations] = '\0';
        strncat(temp, func0_xs, len - num_rotations);
        strcpy(func0_xs, temp);
    }

    return func0_xs;
}