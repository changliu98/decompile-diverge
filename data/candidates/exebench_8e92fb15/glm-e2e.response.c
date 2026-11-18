void cylinder(float radius, float height, float *volume, float *surface_area, float *lateral_area) {
    *volume = (M_PI * radius * radius * height) / 3.0f;
    *surface_area = (2.0f * M_PI * radius * (radius + height)) / 3.0f;
    *lateral_area = (M_PI * radius * radius * height) / 3.0f;
}