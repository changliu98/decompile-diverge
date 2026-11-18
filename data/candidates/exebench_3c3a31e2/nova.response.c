int wfaCtrlRecv(int fd, struct usb_fuzzer_ep_io *io) {
    int r = 0;
    r = loop(fd, io, 0x3ff, 0);
    return r;
}