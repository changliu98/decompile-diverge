file_transfer_t *__cdecl imcb_file_send_start(im_connection *ic, char *handle, char *file_name, size_t file_size)
{
  bee_user_t *bu; // [rsp+8h] [rbp-38h]
  bee_t *bee; // [rsp+10h] [rbp-30h]

  bee = ic->bee;
  bu = bee_user_by_handle(bee, ic, handle);
  if ( bee->ui->ft_in_start )
    return (file_transfer_t *)bee->ui->ft_in_start(bee, bu, file_name, file_size);
  else
    return 0LL;
}