int __cdecl resize_height(double original_width, double target_width, double original_height)
{
    double scaling_factor = target_width / original_width;
    double new_height = original_height * scaling_factor;
    
    return (int)round(new_height);
}