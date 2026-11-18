static unsigned long it_advance(unsigned long psr)
{
 unsigned long it;
 if (psr & (PSR_IT_MASK | PSR_IT_MASK_EX)) {
  it = psr & PSR_IT_MASK;
  it = (it << 1) | (it >> 17);
  return (psr & ~(PSR_IT_MASK | PSR_IT_MASK_EX)) | it |
      PSR_THUMB | PSR_THUMB_EX;
 }
 return psr & ~PSR_IT_MASK;
}