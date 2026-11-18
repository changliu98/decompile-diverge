char *gf_get_next_token(gf_struct * s, int pbreak)
{
 int i, c, go = 1, quote = 0;

 gf_bt_check_line(s);

 i = 0;
 while(go) {
  if(s->cpos + i == s->btlen) break;
  c = *(s->btp + s->cpos + i);
  if(c == '"') {
   if(quote == 0) quote = 1; else quote = 0;
   s->cpos++;
   if(s->cpos + i == s->btlen) break;
   continue;
  }
  if(quote) {
   *(s->token + i) = *(s->btp + s->cpos + i);
   i++;
   if(s->cpos + i == s->btlen) break;
   continue;
  }

  switch(c) {
  case '\0':
  case '\r':
  case '\n':
  case ' ':
  case '\t':
  case ',':
  case '.':
  case '[':
  case ']':
  case '{':
  case '}':
   go = 0;
   break;
  default:
   if(pbreak) go = 0;
  }
  if(go == 0) break;
  i++;
 }
 *(s->token + i) = '\0';
 s->cpos += i;
 return s->token;
}