struct file_transfer *imcb_file_send_start(struct im_connection *ic, const char *handle, const char *file_name, size_t file_size) {
    struct proto_data *proto_data = ic->proto_data;
    struct bee_user *bu = bee_user_by_handle(proto_data, ic, handle);
    struct file_transfer *ft = NULL;

    if (proto_data->file_send_start != NULL) {
        ft = proto_data->file_send_start(proto_data, bu, file_name, file_size);
    }

    return ft;
}