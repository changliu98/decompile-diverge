size_t xfs_cui_log_format_sizeof(uint nr)

{
  uint nr_local;
  
  return (ulong)nr * 4 + 4;
}