bool setsockopt_needs_rtnl(int level) {
    return level >= 128 && level <= 139;
}