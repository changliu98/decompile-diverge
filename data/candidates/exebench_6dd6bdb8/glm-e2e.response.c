void get_grid_address_from_index(struct Point *out, long index, struct Grid *grid) {
    long area = grid->width * grid->height;
    
    // x = index % grid->width
    out->x = index % grid->width;
    
    // y = (index / area) % grid->height
    out->y = (index / area) % grid->height;
    
    // z = index / area
    out->z = index / area;
}