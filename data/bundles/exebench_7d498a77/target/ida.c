int __cdecl get_priority(long pid, int *priority)
{
  *priority = getpriority(__priority_which::PRIO_PROCESS, pid);
  return *__errno_location();
}