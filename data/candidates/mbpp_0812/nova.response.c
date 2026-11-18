char *func0(char *filename) {
    int length = strlen(filename);
    if (length > 4 && strcmp(filename + (length - 4), ".txt") == 0) {
        filename[length - 4] = '\0';
        strcat(filename, "out.txt");
    }
    return filename;
}