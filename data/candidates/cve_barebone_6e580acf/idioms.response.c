void *xf_Pointer_get_window(struct _xfContext *xfc)
{
    if (xfc == ((void *)0))
        return ((void *)0);
    if (xfc->remote_app)
    {
        if (xfc->appWindow == ((void *)0))
            return ((void *)0);
        return xfc->appWindow->handle;
    }
    if (xfc->window == ((void *)0))
        return ((void *)0);
    return xfc->window->handle;
}