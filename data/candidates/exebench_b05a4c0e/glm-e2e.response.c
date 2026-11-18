void grid_point_to_grid_double(int *out, int point, int *dims, int *coords) {
    int i;
    int temp[3];
    
    // temp[0] = point / (dims[0] * dims[1])
    temp[0] = point / (dims[0] * dims[1]);
    
    // temp[1] = (point - temp[0] * dims[0] * dims[1]) / dims[0]
    temp[1] = (point - temp[0] * dims[0] * dims[1]) / dims[0];
    
    // temp[2] = point % dims[0]
    temp[2] = point % dims[0];
    
    // Loop to compute the final output coordinates
    for (i = 0; i < 3; i++) {
        out[i] = (temp[i] * 2) + coords[i];
    }
}