void rfft1pt(struct iop *ioptr)
{
  float t = ioptr->io1;
  ioptr->io1 = ioptr->io0 - t;
  ioptr->io0 = t + ioptr->io1;
}