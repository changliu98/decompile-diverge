int get_next_hash(int iPriorHash)
{
  return (HASHTABLE_NSLOT - 1) & (iPriorHash + 1);
}