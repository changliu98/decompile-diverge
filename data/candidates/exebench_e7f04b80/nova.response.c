int deo_pipe(int *sx, int *sy) {
    int error;
    struct winsize size;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == 0) {
        *sx = size.ws_col;
        *sy = size.ws_row;
        error = 0;
    } else {
        error = errno;
    }

    return error;
}