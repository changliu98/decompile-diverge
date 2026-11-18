int bulbSwitch(int* bulbs, int bulbsSize) {
    int i = 0, j = 0;
    int first, last, temp;
    int count = 0;

    while (1) {
        if (i >= bulbsSize)
            break;

        if (bulbs[i] < 11) {
            i++;
            continue;
        }

        last = bulbs[i] % 10;
        temp = bulbs[i];
        while (temp >= 10) {
            temp /= 10;
        }
        first = temp;

        if (first % 2 == 1 && last % 2 == 1)
            count++;

        i++;
    }

    return count;
}