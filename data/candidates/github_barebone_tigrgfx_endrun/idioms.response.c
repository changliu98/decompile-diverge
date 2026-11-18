void endrun(struct save *s)
{
  s->runlen--;
  literal(s, s->prev);
  if (s->runlen >= 67)
    encodelen(s, 257 + 4, 4, s->runlen - 67);
  else if (s->runlen >= 35)
    encodelen(s, 257 + 3, 3, s->runlen - 35);
  else if (s->runlen >= 19)
    encodelen(s, 257 + 2, 2, s->runlen - 19);
  else if (s->runlen >= 11)
    encodelen(s, 257 + 1, 1, s->runlen - 11);
  else if (s->runlen >= 3)
    encodelen(s, 257 + 0, 0, s->runlen - 3);
  else
    while (s->runlen-- > 0)
      literal(s, s->prev);
}