int lone_survivor(int *soldiers, int count) {
    int i = 0;
    int survivor;

    while (1) {
        if (i < count) {
            if (soldiers[i] % 2) {
                survivor = soldiers[i];
                break;
            } else {
                i++;
            }
        } else {
            survivor = -1;
            break;
        }
    }

    return survivor;
}