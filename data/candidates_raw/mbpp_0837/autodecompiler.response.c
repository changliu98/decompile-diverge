int main() {
    int x = 1;
    int y = 1;
    int c = 0;
    int i = 0;
    while (1) {
        if (i < x) {
            c = c + (2*i+1)*(2*i+1)*(2*i+1);
            i = i + 1;
        } else {
            break;
        }
    }
    return c;
}