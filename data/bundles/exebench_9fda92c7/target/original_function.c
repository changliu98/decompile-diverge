void reverse(char* s) {
    char *start, *end;
    char buf[2];

    start = end = s;

    while(*end++);

    end -= 2;

    while(start < end) {
        buf[0] = *start;
        buf[1] = *end;

        *start = buf[1];
        *end = buf[0];

        end--;
        start++;
    }
}