static const char *func0(const char *name) {
    const char *p;
    char buf[10];
    int ret;

    p = "/sys/class/ieee80211/";
    ret = readlink_safe(buf, p, sizeof(buf));
    if (ret)
        p = "/proc/sys/net/ieee80211/";
    else {
        ret = readlink_safe(buf, name, 0);
        if (ret == 0)
            p = "/sys/class/ieee80211/";
        else if (ret == 1)
            p = "/proc/sys/net/ieee80211/";
        else
            p = "/sys/class/net/";
    }
    return p;
}