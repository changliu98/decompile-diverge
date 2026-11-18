int
VGAGetModeInfo(int mode, struct vgarec *v)
{
    int ret;

    if (v == NULL) {
 ret = 4096;
    } else {
 v->xres = 31;
 ret = 0;
    }
    return (ret);
}