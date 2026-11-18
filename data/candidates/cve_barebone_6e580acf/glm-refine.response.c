Window xf_Pointer_get_window(xfContext *xfc)
{
    if (!xfc)
        return 0;

    if (xfc->remote_app)
        return xfc->appWindow ? xfc->appWindow->handle : 0;

    return xfc->window ? xfc->window->handle : 0;
}