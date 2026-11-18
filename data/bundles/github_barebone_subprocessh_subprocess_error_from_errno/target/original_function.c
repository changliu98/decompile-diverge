int subprocess_error_from_errno(int error) {
  switch (error) {
  case ENOENT:
  case ENOTDIR:
    return subprocess_error_not_found;
  case EACCES:
  case EPERM:
    return subprocess_error_permission_denied;
  case EMFILE:
  case ENFILE:
  case ENOMEM:
    return subprocess_error_no_memory;
  default:
    return subprocess_error_unknown;
  }
}