int __cdecl walNextHash(int iPriorHash)
{
  return (iPriorHash + 1) & (HASHTABLE_NSLOT - 1);
}