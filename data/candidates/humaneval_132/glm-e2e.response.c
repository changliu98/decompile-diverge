int func0(const char *str) {
    int balance = 0;
    int max_balance = 0;
    int i = 0;
    int result;

    while (i < strlen(str)) {
        if (str[i] == '[') {
            balance++;
        } else if (str[i] == ']') {
            balance--;
        }

        if (balance < 0) {
            balance = 0;
        }

        if (balance > max_balance) {
            max_balance = balance;
        }

        if (balance > max_balance - 2) {
            result = 1;
        } else {
            result = 0;
            return result;
        }

        i++;
    }

    result = 0;
    return result;
}