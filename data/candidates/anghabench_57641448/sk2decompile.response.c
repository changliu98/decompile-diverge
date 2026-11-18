int ui_select(int id) {
  if (selected_id == 0) {
    selected_id = id;
  }
  return 1;
}