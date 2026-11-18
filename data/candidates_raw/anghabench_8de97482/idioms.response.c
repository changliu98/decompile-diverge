static inline int get_next_hash(int iPriorHash)
{
  return ( ( iPriorHash + 1 ) & ( HASHTABLE_NSLOT - 1 ) );
}