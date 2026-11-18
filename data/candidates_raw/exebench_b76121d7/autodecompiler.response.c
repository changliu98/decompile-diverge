void
Cudd_EnableGarbageCollection(
  DdManager * dd,
  int enable)
{
    dd->gcEnabled |= enable;

}