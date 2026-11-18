void agrega(int *head,int *tail,int i,int *ll)

{
  int *ll_local;
  int i_local;
  int *tail_local;
  int *head_local;
  
  if (*head == -1) {
    *head = i;
    *tail = i;
  }
  else {
    ll[*tail] = i;
    *tail = i;
  }
  ll[*tail] = -1;
  return;
}