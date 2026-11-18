int psys_getpriority(void *argp)
{
  struct a *args = (struct a *)argp;
  args->priority = getpriority(__priority_which::PRIO_PROCESS, args->pid);
  return (*__errno_location ());
}