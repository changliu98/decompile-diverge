int resize_height(double old_width, double old_height, double new_width) {
    double scale = old_height / old_width;
    double new_height = new_width * scale + 0.5;
    return (int)new_height;
}