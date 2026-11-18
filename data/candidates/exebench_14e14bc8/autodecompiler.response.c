void c_sysconf_(int *name, long int *value, int *error) {
    *value = sysconf(*name);
    *error = (*___errno_location());
}