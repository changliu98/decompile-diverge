static const char *func0(const char *name) {
    struct io_capture_t io_capture;
    const char *ret;
    int rc = io_capture_start(&io_capture);
    if (rc) {
        ret = "<error>";
    } else {
        rc = io_capture_run(&io_capture, name, true, &io_capture_redirect_to_child, NULL);
        ret = io_capture_stop(&io_capture);
        if (rc == 0) {
            ret = "<success>";
        } else {
            ret = "<error>";
        }
    }
    return ret;
}