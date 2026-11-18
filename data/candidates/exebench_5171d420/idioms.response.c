int _inverse_rot(struct t_res *res, struct t_size *size)
{
  if (res->width == 0 || res->height == 0)
    return 1;
  size->width = 0;
  size->height = (1024 * 1024) / res->height;
  size->depth = (1024 * 1024) / res->width;
  size->left = 0;
  size->right = -size->depth * res->right / 1024;
  size->top = -size->height * res->top / 1024;
  return 0;
}