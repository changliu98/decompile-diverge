void
spin_unlock(
  DdManager * unique)
{
    unique->realignZ = 0;
    return;

}