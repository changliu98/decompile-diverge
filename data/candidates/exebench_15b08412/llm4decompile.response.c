int
div_dbl(
 dblint *op,
 dblint div
)
{
 if (div == 0 || div <= op->lo)
  return 1;

 op->hi = op->hi / div;
 op->lo = op->lo / div;

 return 0;
}