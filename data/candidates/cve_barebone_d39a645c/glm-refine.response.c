void __cdecl xf_AppWindowDestroyImage(xfAppWindow *appWindow)
{
    // Check if the appWindow pointer and its image member are valid
    if (appWindow && appWindow->image)
    {
        // Clear the data pointer to prevent dangling references or double-frees 
        // if ossCloseThread attempts to clean up associated buffers.
        appWindow->image->data = NULL;
        
        // Close/cleanup the thread or resource associated with the image
        ossCloseThread(appWindow->image);
        
        // Nullify the pointer to mark the resource as destroyed
        appWindow->image = NULL;
    }
}