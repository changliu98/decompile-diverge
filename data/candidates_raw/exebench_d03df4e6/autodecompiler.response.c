void
Cudd_SetMaxCacheHard(
  DdManager * manager,
  int hardlimit)
{
    manager->maxCacheHard = hardlimit;
    return;

}