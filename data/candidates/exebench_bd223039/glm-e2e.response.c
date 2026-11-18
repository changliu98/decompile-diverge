void clearMarker(char *str, char marker) {
    char *ptr = strchr(str, marker);
    if (ptr != NULL) {
        *ptr = '\0';
    }
}