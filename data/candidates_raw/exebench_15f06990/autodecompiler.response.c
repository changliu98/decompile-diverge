void
cuddCacheFlush(
  DdManager * table)
{
    table->cacheLast = 0;
    return;

}