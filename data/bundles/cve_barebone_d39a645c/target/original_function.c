static void xf_AppWindowDestroyImage(xfAppWindow* appWindow)
{
	WINPR_ASSERT(appWindow);
	if (appWindow->image)
	{
		appWindow->image->data = NULL;
		XDestroyImage(appWindow->image);
		appWindow->image = NULL;
	}
}