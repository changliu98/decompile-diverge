char * freezer_state_strs(uint state)

{
  uint state_local;
  char *local_10;
  
  if ((state & CGROUP_FROZEN) == 0) {
    if ((state & CGROUP_FREEZING) == 0) {
      local_10 = "THAWED";
    }
    else {
      local_10 = "FREEZING";
    }
  }
  else {
    local_10 = "FROZEN";
  }
  return local_10;
}