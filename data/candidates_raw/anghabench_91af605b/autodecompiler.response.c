__attribute__((used)) static const char *cgroup_state_to_string(CGroupMask mask) {
        const char *state;

        if (mask & CGROUP_FROZEN)
                state = "FROZEN";
        else if (mask & CGROUP_FREEZING)
                state = "FREEZING";
        else
                state = "THAWED";

        return state;
}