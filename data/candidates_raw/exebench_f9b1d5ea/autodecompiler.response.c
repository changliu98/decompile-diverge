int escape_char(struct token *tok, struct token *new_tok)
{
 int ret;

 if (tok->type == '\\') {
  switch (tok->val) {
  case 'a':
   new_tok->val = '\a';
   ret = 1;
   break;
  case 'b':
   new_tok->val = '\b';
   ret = 1;
   break;
  case 'f':
   new_tok->val = '\f';
   ret = 1;
   break;
  case 'n':
   new_tok->val = '\n';
   ret = 1;
   break;
  case 'r':
   new_tok->val = '\r';
   ret = 1;
   break;
  case 't':
   new_tok->val = '\t';
   ret = 1;
   break;
  case 'v':
   new_tok->val = '\v';
   ret = 1;
   break;
  case '?':
   new_tok->val = '?';
   ret = 1;
   break;
  case '\'':
   new_tok->val = '\'';
   ret = 1;
   break;
  case '\"':
   new_tok->val = '\"';
   ret = 1;
   break;
  default:

   break;
  }
 } else {
  *new_tok = *tok;
  ret = 0;
 }

 return ret;
}