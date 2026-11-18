void collectgarbage(FICL_VM *pVM) {
  int i;
  for (i = 0; i < pVM->nrxs; i++) {
    fe_mark(pVM, pVM->xstack[i]);
  }
  fe_mark(pVM, pVM->here);
  for (i = 0; i < pVM->nrfree; i++) {
    FICL_WORD *pFW = &pVM->free[i];
    if ((((pFW->flags) & 1) ? ((int)((pFW->flags) >> 2)) : 0) != 1) {
      if ((((pFW->flags) & 2) ? 0 : 1)) {
        pFW->flags = ((pFW->flags) & ~2);
      } else {
        if ((((pFW->flags) & 1) ? ((int)((pFW->flags) >> 2)) : 0) == 10) {
          if (pVM->hw.free_word) {
            pVM->hw.free_word(pVM, pFW);
          }
        }
        pFW->flags = 5;
        pFW->link = pVM->free_list;
        pVM->free_list = pFW;
      }
    }
  }
}