void image_fit(int source_w, int source_h, int target_w, int target_h, int *end_w, int *end_h, char type)
{
    float source_r = (float)source_h / (float)source_w;
    float target_r = (float)target_h / (float)target_w;

    if (type < 1 || type > 2)
    {
        type = source_r < target_r ? 1 : 2;
    }

    if (type == 1)
    {
        *end_h = (int)(target_w * source_r);
        *end_w = target_w;
    }
    else
    {
        *end_w = (int)(target_h / source_r);
        *end_h = target_h;
    }
}