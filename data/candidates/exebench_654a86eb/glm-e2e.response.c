void previousPage(int arg1, int *currentPage) {
    if (*currentPage != 0) {
        *currentPage = *currentPage - 1;
    }
}