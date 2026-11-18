int func0(int a, int b) {
    int i;
    if (a > b)
        i = a;
    else
        i = b;
    while (1) {
        if (i % a == 0 && i % b == 0)
            return i;
        else
            i++;
    }
}