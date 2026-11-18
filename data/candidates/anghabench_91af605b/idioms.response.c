char *freezer_state_strs(int state)
{
    if (state & CGROUP_FROZEN)
        return "FROZEN";
    if (state & CGROUP_FREEZING)
        return "FREEZING";
    return "THAWED";
}