xf_Window xf_Pointer_get_window(xf_Pointer* pointer) {
  if (!pointer) return 0;
  if (pointer->is_mouse) {
    if (pointer->mouse)
      return pointer->mouse->window;
    else
      return 0;
  } else {
    if (pointer->touch)
      return pointer->touch->window;
    else
      return 0;
  }
}