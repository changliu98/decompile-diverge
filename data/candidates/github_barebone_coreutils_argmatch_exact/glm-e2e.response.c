long argmatch_exact(const char *arg, const char * const *args) {
    long i = 0;
    long ret;

    while (args[i] != NULL) {
        if (strcmp(args[i], arg) == 0) {
            ret = i;
            return ret;
        }
        i++;
    }
    
    ret = -1;
    return ret;
}