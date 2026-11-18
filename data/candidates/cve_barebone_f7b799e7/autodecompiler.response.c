static void
color_cmyk_to_rgb(gdev_prn_print_page_info_t * pinfo)
{
    unsigned w = pinfo->cmyk_data[0].width;
    unsigned h = pinfo->cmyk_data[0].height;
    unsigned i, size;

    if (pinfo->cmyk_num_components < 4)
 return;
    size = w * h;
    {
 float c_scale =
     1.0 / ((float)((1 << pinfo->cmyk_data[0].depth) - 1));
 float m_scale =
     1.0 / ((float)((1 << pinfo->cmyk_data[1].depth) - 1));
 float y_scale =
     1.0 / ((float)((1 << pinfo->cmyk_data[2].depth) - 1));
 float k_scale =
     1.0 / ((float)((1 << pinfo->cmyk_data[3].depth) - 1));

 for (i = 0; i < size; ++i) {
     float c = pinfo->cmyk_data[0].data[i] * c_scale;
     float m = pinfo->cmyk_data[1].data[i] * m_scale;
     float y = pinfo->cmyk_data[2].data[i] * y_scale;
     float k = pinfo->cmyk_data[3].data[i] * k_scale;

     c = 1.0 - c;
     m = 1.0 - m;
     y = 1.0 - y;
     k = 1.0 - k;
     pinfo->cmyk_data[0].data[i] = (byte)(c * 255.0);
     pinfo->cmyk_data[1].data[i] = (byte)(m * 255.0);
     pinfo->cmyk_data[2].data[i] = (byte)(y * 255.0);
 }
    }
    free(pinfo->cmyk_data[3].data);
    pinfo->cmyk_data[3].data = NULL;
    pinfo->cmyk_data[0].depth = 8;
    pinfo->cmyk_data[1].depth = 8;
    pinfo->cmyk_data[2].depth = 8;
    pinfo->cmyk_num_components--;
    pinfo->cmyk_is_inverted = ((bool)1);
    for (i = 3; i < pinfo->cmyk_num_components; ++i)
 memcpy(&pinfo->cmyk_data[i], &pinfo->cmyk_data[i + 1],
        sizeof(pinfo->cmyk_data[0]));
}