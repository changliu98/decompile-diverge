void SetShort(struct stack *st)
{
  st->size = 387;
  st->top = 0;
  st->data = (int *)malloc(st->size * sizeof(int));
}