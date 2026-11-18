void add_to_free_list(int *head, int *tail, int e, int *next) {
  if (*head == -1) {
    *head = e;
    *tail = e;
  } else {
    next[*tail] = e;
    *tail = e;
  }
  next[*tail] = -1;
}