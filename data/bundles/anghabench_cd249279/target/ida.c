int __cdecl pid_to_processor_id(int pid)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; i < ncpus; ++i )
  {
    if ( *(_DWORD *)(cpu_tasks + 4LL * i) == pid )
      return i;
  }
  return -1;
}