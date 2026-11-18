void Mat_GetLibraryVersion(int *major, int *minor, int *release) {
    if (major != NULL) {
        *major = 1;
    }
    if (minor != NULL) {
        *minor = 5;
    }
    if (release != NULL) {
        *release = 9;
    }
}