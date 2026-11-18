static void func0(struct mpgl_osd *ctx, struct mp_osd_res res,
                               const struct mp_osd_res *display_res)
{
    ptrdiff_t display_width = display_res->w * display_res->h;
    ctx->osd_res.w = res.w % display_res->w;
    ctx->osd_res.h = res.h / display_width;
    ctx->osd_res_scale = (res.h - ctx->osd_res.h * display_width) / display_res->h;
}