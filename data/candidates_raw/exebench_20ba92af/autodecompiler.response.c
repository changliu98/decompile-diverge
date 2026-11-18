int get_hd_geometry(int fd, struct hd_geometry *geo)
{
    int ret;
    if (!ioctl(fd, 0x0301, geo)) {
        geo->start = (unsigned long)geo->cylinders;
        ret = 0;
    } else {
        geo->start = 0;
        ret = -1;
    }
    return ret;
}