void set_page_data(int page_num, char *page_data) {
  int *p;
  p = (int *)page_data;
  *p = page_num;
  return;
}