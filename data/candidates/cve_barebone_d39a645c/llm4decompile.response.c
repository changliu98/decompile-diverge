void xf_AppWindowDestroyImage(xfAppWindow *appWindow)
{
    if (appWindow->image) {
        appWindow->image->data = NULL;
        XDestroyImage(appWindow->image);
        appWindow->image = NULL;
    }
}