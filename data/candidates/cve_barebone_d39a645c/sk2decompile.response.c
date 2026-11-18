void xf_AppWindowDestroyImage(xf_AppWindow* window) {
  if (window->imageThread) {
    window->imageThread->arg = NULL;
    ossCloseThread(window->imageThread);
    window->imageThread = NULL;
  }
}