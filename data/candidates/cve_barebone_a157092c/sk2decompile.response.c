static reg_t *get_register(int reg, int save) {
  reg_t *r;
  int i;
  get_yank_register(reg, 0);
  r = alloc(sizeof(reg_t));
  if (r == NULL) return NULL;
  r->lines = yank_reg->lines;
  r->nlines = yank_reg->nlines;
  r->type = yank_reg->type;
  if (save) {
    if (r->nlines != 0)
      r->lines = alloc(r->nlines * sizeof(char *));
    else
      r->lines = NULL;
    if (r->lines != NULL)
      for (i = 0; i < r->nlines; i++) r->lines[i] = vim_strsave(yank_reg->lines[i]);
  } else
    yank_reg->lines = NULL;
  return r;
}