int resize_height(double old_width, double new_width, double old_height) {
    return (int)(old_height * (new_width / old_width) + 0.5);
}