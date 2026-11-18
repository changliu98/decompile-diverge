char *func0(int x1, int y1, int x2, int y2, int x3, int y3) {
    char *yes = "YES";
    char *no = "NO";
    int check = (x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2));
    if (check == 0) {
        return no;
    } else {
        return yes;
    }
}