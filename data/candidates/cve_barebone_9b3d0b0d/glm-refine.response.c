Window xf_Pointer_get_window(xfContext *xfc)
{
    if (!xfc)
    {
        WLog_Print_dbg_tag(
            "com.freerdp.client.x11",
            3u,
            0xA0uLL,
            "/work/harness.c",
            "xf_Pointer_get_window",
            "xf_Pointer: Invalid context");
        return 0LL;
    }

    if (xfc->remote_app)
    {
        if (xfc->appWindow)
            return xfc->appWindow->handle;

        WLog_Print_dbg_tag(
            "com.freerdp.client.x11",
            3u,
            0xA7uLL,
            "/work/harness.c",
            "xf_Pointer_get_window",
            "xf_Pointer: Invalid appWindow");
        return 0LL;
    }

    if (xfc->window)
        return xfc->window->handle;

    WLog_Print_dbg_tag(
        "com.freerdp.client.x11",
        3u,
        0xB0uLL,
        "/work/harness.c",
        "xf_Pointer_get_window",
        "xf_Pointer: Invalid window");
    return 0LL;
}