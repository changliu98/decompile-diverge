void func0(int *c) {
    int d = *c;
    if (d >= 'a' && d <= 'i')
        ;
    else if (d >= 'j' && d <= 'r')
        ;
    else if (d >='s' && d <= 'z')
        ;
    else
        *c = d + 65 - 'a';
}