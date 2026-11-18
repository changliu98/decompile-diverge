void previousPage(int totalPages, int *currentPage) {
  if (*currentPage == 0) {
    return;
  } else {
    *currentPage = *currentPage - 1;
  }
}