/*
 * Converts a cgroup freezer state bitmask into its corresponding string representation.
 *
 * @param state The current freezer state flags (e.g., CGROUP_FROZEN, CGROUP_FREEZING).
 * @return A static string literal representing the state:
 *         - "FROZEN" if the CGROUP_FROZEN flag is set.
 *         - "FREEZING" if the CGROUP_FREEZING flag is set.
 *         - "THAWED" if neither flag is set.
 */
char * freezer_state_strs(uint freezer_state)
{
    // Check if the cgroup is in the frozen state
    if (freezer_state & CGROUP_FROZEN) {
        return "FROZEN";
    }
    // Check if the cgroup is in the process of freezing
    if (freezer_state & CGROUP_FREEZING) {
        return "FREEZING";
    }
    // Default to thawed state if neither frozen nor freezing
    return "THAWED";
}