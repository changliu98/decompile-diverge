int number(char *string) {
    int counter = 0;
    int i = 0;
    while (1) {
        size_t length = strlen(string);
        if (i >= length) {
            break;
        }
        switch (string[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                counter++;
                break;
            default:
                break;
        }
        i++;
    }
    return counter;
}