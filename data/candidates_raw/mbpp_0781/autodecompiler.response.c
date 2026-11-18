char* check(int n) {
    int count = 0;
    int i = 1;
    while (1) {
        if (i >= (int)(sqrt(n)) + 2) {
            break;
        }
        if (n % i == 0) {
            if (n / i == i) {
                count++;
            } else {
                count += 2;
            }
        }
        i++;
    }

    char *result;
    if (count % 2 == 0) {
        result = "Even";
    } else {
        result = "Odd";
    }
    return result;
}