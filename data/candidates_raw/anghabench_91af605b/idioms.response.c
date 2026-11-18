char *cgroup_state_to_str(int state)
{
    if (state & CGROUP_FROZEN)
        return "FROZEN";
    if (state & CGROUP_FREEZING)
        return "FREEZING";
    return "THAWED";
}