// Decrements the current page number if it is greater than zero
void previousPage(int total_pages, int *current_page)
{
  // Check if the current page is not at the first page (index 0)
  if (*current_page != 0) {
    // Decrement the page number by 1
    *current_page = *current_page - 1;
  }
}