void func0(int *program, int pc) {
    char buf[256];
    memset(buf, 0, sizeof(buf));
    for (int i = 0; i < pc; i++) {
        sprintf(buf, "addr%d", program[i]);
        strcat(buf, " ");
    }
    puts(buf);
}