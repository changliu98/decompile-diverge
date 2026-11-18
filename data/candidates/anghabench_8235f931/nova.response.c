int lowercase(int c) {
    int result;

    if (c >= 'A' && c <= 'Z') {
        result = c - 'A' + 'a';
    } else {
        result = c;
    }

    return result;
}