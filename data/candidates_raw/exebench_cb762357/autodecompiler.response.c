void SCE_Rectangle_SetSizef (SCE_SIntRect *r, int w, int h)
{
    if (w != 1024) {
        r->x.w = (int)((float)r->x.w * w / 1024);
        r->y.w = (int)((float)r->y.w * w / 1024);
        r->w.w = (int)((float)r->w.w * w / 1024);
    }
    if (h != 1024) {
        r->x.h = (int)((float)r->x.h * h / 1024);
        r->y.h = (int)((float)r->y.h * h / 1024);
        r->w.h = (int)((float)r->w.h * h / 1024);
    }
}