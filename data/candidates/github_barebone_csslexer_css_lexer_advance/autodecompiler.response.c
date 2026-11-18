void css_lexer_advance(struct lexbuf *l)
{
 if (l->lexpos < l->lexlen) {
  l->lexpos++;
  l->lexchar = l->lexbuf[l->lexpos];

  switch (l->lexchar) {
  case '\n':
   l->lexline++;
   l->lexcolumn = 0;
   break;
  default:
   l->lexcolumn++;
  }
 } else {
  printf("(CSS): Lexer out of range.\n");
 }
}