void swap(struct _cell *clra, struct _cell *clrb)
{
  int t = clra->val;
  clra->val = clrb->val;
  clrb->val = t;
}