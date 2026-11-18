__attribute__((noinline))
static Window xf_Pointer_get_window(xfContext* xfc)
{
	if (!xfc)
	{
		WLog_WARN(TAG, "xf_Pointer: Invalid context");
		return 0;
	}
	if (xfc->remote_app)
	{
		if (!xfc->appWindow)
		{
			WLog_WARN(TAG, "xf_Pointer: Invalid appWindow");
			return 0;
		}
		return xfc->appWindow->handle;
	}
	else
	{
		if (!xfc->window)
		{
			WLog_WARN(TAG, "xf_Pointer: Invalid window");
			return 0;
		}
		return xfc->window->handle;
	}
}