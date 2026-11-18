int error(struct error_handler *h) {
    return ++h->error_count;
}