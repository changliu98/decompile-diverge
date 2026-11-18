file_transfer_t *
imcb_file_send_start(im_connection *ic,char *handle,char *file_name,size_t file_size)

{
  bee_t *bee_00;
  bee_user_t *pbVar1;
  bee_user_t *bu;
  bee_t *bee;
  size_t file_size_local;
  char *file_name_local;
  char *handle_local;
  im_connection *ic_local;
  file_transfer *local_10;
  
  bee_00 = ic->bee;
  pbVar1 = bee_user_by_handle(bee_00,ic,handle);
  if (bee_00->ui->ft_in_start ==
      (_func_file_transfer_ptr_bee_t_ptr_bee_user_t_ptr_char_ptr_size_t *)0x0) {
    local_10 = (file_transfer *)0x0;
  }
  else {
    local_10 = (*bee_00->ui->ft_in_start)(bee_00,pbVar1,file_name,file_size);
  }
  return local_10;
}