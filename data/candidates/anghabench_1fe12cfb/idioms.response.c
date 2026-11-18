int walNextHash(int iPriorHash)
{
  return (HASHTABLE_NSLOT - 1) & (iPriorHash + 1);
}