void validate_st_entry(struct iset *iset)
{
  ((iset->bits)[((iset->val) / (8 * (unsigned long) sizeof(unsigned long)))] &= ~((unsigned long) 1 << ((iset->val) % (8 * (unsigned long) sizeof(unsigned long)))));
}