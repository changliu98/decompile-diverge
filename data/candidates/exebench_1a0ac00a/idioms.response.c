void agrega(int *head, int *tail, int i, int *ll)
{
  if (*head == -1)
    *head = i;
  else
    ll[*tail] = i;
  *tail = i;
  ll[*tail] = -1;
}