int subprocess_error_from_errno(int errno_value) {
  switch (errno_value) {
    case 1:
      return -5;
    case 2:
      return -4;
    case 12:
      return -6;
    case 13:
      return -5;
    case 20:
      return -4;
    case 23:
    case 24:
      return -6;
    default:
      return -1;
  }
}