void xf_AppWindowDestroyImage(AppWindow *appWindow) {
    if (appWindow->image != NULL) {
        appWindow->image->data = NULL;
        XDestroyImage(appWindow->image);
        appWindow->image = NULL;
    }
}