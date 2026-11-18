int func0(int *list, int size) {
    int i;
    char ok;
    int changes = 0;

    if (size == 0) {
 ok = 1;
    } else {
 for (i=1; i<size; i++) {
     if (list[i] < list[i-1]) changes++;
 }
 if (list[size-1] > list[0]) changes++;
 if (changes <= 1) ok = 1;
 else ok = 0;
    }

    return ok;
}