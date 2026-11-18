file_transfer_t *imcb_file_send_start(im_connection *ic, char *handle, char *file_name, size_t file_size) {
    bee_t *bee = ic->bee;
    bee_user_t *bu = bee_user_by_handle(bee, ic, handle);
    file_transfer_t *ft = NULL;

    if (bee->ui->ft_in_start)
        ft = bee->ui->ft_in_start(bee, bu, file_name, file_size);

    return ft;
}