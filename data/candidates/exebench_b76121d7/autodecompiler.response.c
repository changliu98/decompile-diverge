void
atomic_or_long(
  DdManager * dd,
  int enable)
{
    dd->gcEnabled |= enable;

}