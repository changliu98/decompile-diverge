const char *freezer_state_strs(int state) {
    const char *str;
    
    if (state & CGROUP_FROZEN) {
        str = "FROZEN"; // 0x2004
    } else if (state & CGROUP_FREEZING) {
        str = "FREEZING"; // 0x200b
    } else {
        str = "THAWED"; // 0x2014
    }
    
    return str;
}