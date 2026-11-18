void xf_AppWindowDestroyImage(xfAppWindow *window)
{
    // Check if the image pointer is valid
    if (window->image) {
        // Clear the data pointer to prevent dangling references
        window->image->data = NULL;
        // Destroy the X11 image resource
        XDestroyImage(window->image);
        // Set the image pointer to NULL to avoid use-after-free
        window->image = NULL;
    }
}