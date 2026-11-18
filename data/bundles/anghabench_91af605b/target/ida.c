const char *__cdecl freezer_state_strs(unsigned int state)
{
  if ( (CGROUP_FROZEN & state) != 0 )
    return "FROZEN";
  if ( (CGROUP_FREEZING & state) != 0 )
    return "FREEZING";
  return "THAWED";
}