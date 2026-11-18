void nextPage(int numPages,int *page)

{
  int *page_local;
  int numPages_local;
  
  if (*page != numPages + -1) {
    *page = *page + 1;
  }
  return;
}