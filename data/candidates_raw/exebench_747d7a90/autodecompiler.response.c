void
child_cleanup (struct child_info *child, int *last_fd, int *n_children)
{
  close (child->fd & ~0xff);
  *last_fd = child->fd;
  (*n_children)++;
}