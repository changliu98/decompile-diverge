Window xf_Pointer_get_window(xfContext *context)
{
    // Check if the context pointer is valid
    if (context == NULL) {
        WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 0xa0, "/work/harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid context");
        return 0;
    }
    // If not in remote app mode, return the main window handle
    if (context->remote_app == 0) {
        // Check if the main window is valid
        if (context->window == NULL) {
            WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 0xb0, "/work/harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid window");
            return 0;
        }
        return context->window->handle;
    }
    // In remote app mode, check if the app window is valid
    if (context->appWindow == NULL) {
        WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 0xa7, "/work/harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid appWindow");
        return 0;
    }
    // Return the remote application window handle
    return context->appWindow->handle;
}