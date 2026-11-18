Window xf_Pointer_get_window(xfContext *context)
{
    // Return 0 if the context pointer is NULL
    if (context == NULL) return 0;

    // If not in remote application mode
    if (context->remote_app == 0) {
        // Return 0 if the main window is NULL
        if (context->window == NULL) return 0;
        // Return the handle of the main window
        return context->window->handle;
    }

    // If in remote application mode, return 0 if the app window is NULL
    if (context->appWindow == NULL) return 0;
    // Return the handle of the application window
    return context->appWindow->handle;
}