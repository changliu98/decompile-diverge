bool MACH0_(void *arg1, int arg2, int arg3) {
    bool result = parse_chained_fixups(arg1, arg2, arg3);
    g_no_tailcall_sink++;
    return result;
}