char *func0(char *numbers)
{
    char *numto[10];
    int count[10];
    memset(count, 0, sizeof(count));
    memcpy(numto, (char *[]) {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}, sizeof(numto));

    char current[6];
    int i, j, k, index;
    index = 0;
    while (*numbers != 0) {
        i = 0;
        while (numbers[i] != ' ' && numbers[i] != 0) {
            current[i] = numbers[i];
            i++;
        }
        current[i] = 0;
        for (j = 0; j < 10; j++) {
            if (!strcmp(current, numto[j])) {
                count[j]++;
                break;
            }
        }
        numbers += i + 1;
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < count[i]; j++) {
            for (k = 0; numto[i][k] != 0; k++) {
                func0::out[index] = numto[i][k];
                index++;
            }
            func0::out[index] = ' ';
            index++;
        }
    }
    if (index > 0) {
        func0::out[index - 1] = 0;
    } else {
        func0::out[0] = 0;
    }
    return func0::out;
}