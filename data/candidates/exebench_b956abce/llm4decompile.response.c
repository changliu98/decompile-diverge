void set_page_data(int potval, void *buf)
{
  int *wordp;
  int word;
  wordp = (int *)buf;
  word = potval;
  *wordp = word;
}