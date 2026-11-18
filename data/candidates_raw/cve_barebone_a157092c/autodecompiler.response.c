static yankreg_T *
get_yank_register_save(
    int reg,
    int copy)
{
    yankreg_T *y_ptr;
    yankreg_T *y_ret;
    int i;

    get_yank_register(reg, NULL);

    y_ptr = (yankreg_T *)alloc((unsigned)sizeof(yankreg_T));
    if (y_ptr == NULL)
    {
 y_ret = NULL;
    }
    else
    {
 *y_ptr = *y_current;
 if (copy)
 {

     if (y_ptr->lines == 0)
  y_ptr->y_array = NULL;
     else
  y_ptr->y_array = (char_u **)alloc((unsigned)(y_ptr->lines * sizeof(char_u *)));

     if (y_ptr->y_array != NULL)
  for (i = 0; ; ++i)
  {
      if (i >= y_ptr->lines)
   break;
      y_ptr->y_array[i] = vim_strsave(y_current->y_array[i]);
  }
 }
 else
 {

     y_current->y_array = NULL;
 }

 y_ret = y_ptr;
    }

    return y_ret;
}