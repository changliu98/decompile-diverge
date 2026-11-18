xf_Window _xf_Pointer_GetWindow(xf_Pointer* context) {
  if (!context) {
    _xf_Error("xf_Pointer: Invalid context");
    return 0;
  }
  if (context->appWindow) {
    if (!context->appWindowContext) {
      _xf_Error("xf_Pointer: Invalid appWindow");
      return 0;
    }
    return context->appWindowContext->window;
  } else {
    if (!context->windowContext) {
      _xf_Error("xf_Pointer: Invalid window");
      return 0;
    }
    return context->windowContext->window;
  }
}