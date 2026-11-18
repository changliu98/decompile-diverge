int walNextHash(int iPriorHash)

{
  int iPriorHash_local;
  
  return iPriorHash + 1U & HASHTABLE_NSLOT - 1U;
}