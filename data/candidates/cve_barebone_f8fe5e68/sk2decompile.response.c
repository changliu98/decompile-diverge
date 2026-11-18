imcb_file_t *imcb_file_send_start(imcb_t *imcb, const char *handle,
                                  const char *filename, unsigned long size) {
  bee_t *bee = imcb->bee;
  bee_user_t *user = bee_user_by_handle(bee, imcb, handle);
  if (bee->imcb_file_class->send_start)
    return bee->imcb_file_class->send_start(bee, user, filename, size);
  return NULL;
}