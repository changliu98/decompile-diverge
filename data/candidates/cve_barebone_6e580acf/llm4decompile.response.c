Window xf_Pointer_get_window(xfContext *xfc)
{
    if (xfc) {
        if (xfc->remote_app) {
            if (xfc->appWindow) {
                return xfc->appWindow->handle;
            } else {
                return 0;
            }
        } else {
            if (xfc->window) {
                return xfc->window->handle;
            } else {
                return 0;
            }
        }
    } else {
        return 0;
    }
}