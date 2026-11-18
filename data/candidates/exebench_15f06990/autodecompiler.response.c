void
sync_unlock(
  DdManager * table)
{
    table->cacheLast = 0;
    return;

}