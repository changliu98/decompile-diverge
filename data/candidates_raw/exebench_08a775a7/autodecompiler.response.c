int next_combination(int *list, int size) {
    int i = 0;
    int ret;

    while (1) {
        char found = i < size && list[i];

        if (!found) {
            break;
        }

        list[i] = 0;
        i++;
    }

    if (i < size) {
        list[i] = 1;
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}