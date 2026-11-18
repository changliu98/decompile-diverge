void __cdecl image_fit(
        unsigned int source_w,
        unsigned int source_h,
        unsigned int target_w,
        unsigned int target_h,
        unsigned int *end_w,
        unsigned int *end_h,
        char type)
{
    // Calculate the source aspect ratio (height / width).
    // The integer casts mimic the original explicit float conversions.
    float source_r = (float)(int)source_h / (float)(int)source_w;

    // If the type is out of bounds (not 1 or 2), auto-determine the fit type.
    if (type < 1 || type > 2)
    {
        // If the target's aspect ratio is greater than the source's,
        // the image is proportionally wider than the target frame.
        // Fit to width (type 1). Otherwise, fit to height (type 2).
        float target_r = (float)(int)target_h / (float)(int)target_w;
        type = (target_r > source_r) ? 1 : 2;
    }

    if (type == 1) 
    {
        // Fit to width: Match target width, scale height based on source aspect ratio.
        *end_w = target_w;
        *end_h = (int)((float)(int)target_w * source_r);
    }
    else 
    {
        // Fit to height: Match target height, scale width based on source aspect ratio.
        *end_h = target_h;
        *end_w = (int)((float)(int)target_h / source_r);
    }
}