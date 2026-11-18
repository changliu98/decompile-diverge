CSSToken * css_lexer_next_token(CSSLexer *lexer)

{
  int iVar1;
  CSSToken *pCVar2;
  char *pcVar3;
  CSSToken *tok;
  CSSLexer *lexer_local;
  
  pCVar2 = _css_lexer_next_token(lexer);
  if ((*pCVar2->value == '@') && (pcVar3 = strstr(pCVar2->value,"font-face"), pcVar3 == (char *)0x0)
     ) {
    pCVar2->special = 1;
  }
  iVar1 = strcmp(pCVar2->value,"to");
  if (iVar1 == 0) {
    pCVar2->type = TOKEN_STATEMENT;
  }
  else {
    iVar1 = strcmp(pCVar2->value,"@media");
    if ((iVar1 == 0) || (iVar1 = strcmp(pCVar2->value,"@page"), iVar1 == 0)) {
      pCVar2->type = TOKEN_ID;
    }
  }
  return pCVar2;
}