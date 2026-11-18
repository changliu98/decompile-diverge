void bar(struct S *s)
{
 s->x = 5;
 if (s->x != 5)
  return;
 s->x = 3;
}