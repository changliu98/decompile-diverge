void iset_del(struct iset *iset)
{
  ((iset->bits)[((iset->val) / (8 * (unsigned long) sizeof(unsigned long)))] &= ~((unsigned long) 1 << ((iset->val) % (8 * (unsigned long) sizeof(unsigned long)))));
}