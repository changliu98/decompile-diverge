void
SN_set_nb_iters(
  DdManager * manager,
  int hardlimit)
{
    manager->maxCacheHard = hardlimit;
    return;

}