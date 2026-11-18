static const char *func0(char *argv[], int argc, char *arg) {
    int i;
    int res;
    char *pattern;
    char buf[80];

    for (i = 0; i < argc; i++) {
        res = sscanf(argv[i], arg, buf);
        if (res!= 0) {
            sprintf(err_msg, "expected numeric argument");
            return "--err";
        } else {
            res = sscanf(buf, "%lf", &pattern);
            if (res == 0) {
                sprintf(err_msg, "expected numeric argument");
                return "--err";
            }
        }
    }
    return "--ok";
}