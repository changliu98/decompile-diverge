struct file_transfer *imcb_file_send_start(struct im_connection *ic, char *handle, char *file_name, unsigned long file_size)
{
  struct bee *bee = ic->bee;
  struct bee_user *bu = bee_user_by_handle(bee, ic, handle);
  if (bee->ui->ft_in_start)
    return (struct file_transfer *)bee->ui->ft_in_start(bee, bu, file_name, file_size);
  return ((void *)0);
}