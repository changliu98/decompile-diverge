static void endrun(deflate_state *s) {
  s->match_length--;
  literal(s, s->lookback);
  if (s->match_length >= 67)
    encodelen(s, 277, 4, s->match_length - 67);
  else if (s->match_length >= 35)
    encodelen(s, 273, 3, s->match_length - 35);
  else if (s->match_length >= 19)
    encodelen(s, 269, 2, s->match_length - 19);
  else if (s->match_length >= 11)
    encodelen(s, 265, 1, s->match_length - 11);
  else if (s->match_length >= 3)
    encodelen(s, 257, 0, s->match_length - 3);
  else
    while (s->match_length--) literal(s, s->lookback);
}