int xf_rail_server_execute_result(void *arg1, void *arg2) {
    assert(arg1 != NULL);
    assert(arg2 != NULL);

    void *context = *(void **)((char *)arg1 + 8);
    assert(context != NULL);

    if (*(unsigned short *)((char *)arg2 + 2) != 0) {
        const char *error_name = error_code_names[*(unsigned short *)((char *)arg2 + 2)];
        unsigned int error_code = *(unsigned int *)((char *)arg2 + 4);
        
        WLog_Print_dbg_tag("librail", 4, 229, "xf_rail_server_execute_result", __FILE__,
                           "RAIL execute result: error: %s (0x%08x)", error_name, error_code);
        
        freerdp_abort_connect_context(context);
    }

    return 0;
}