int stbtt__close_shape(stbtt_vertex *path_vertices, int vertex_count, int prev_was_off_curve, int start_was_off_curve,
                       stbtt_int32 start_x, stbtt_int32 start_y, stbtt_int32 start_control_x, stbtt_int32 start_control_y, stbtt_int32 current_x,
                       stbtt_int32 current_y)
{
    // If the starting point was not an off-curve point
    if (start_was_off_curve == 0) {
        // If the previous point was also not an off-curve point, add a line segment to close the shape
        if (prev_was_off_curve == 0) {
            stbtt_setvertex(path_vertices + vertex_count, '\x02', start_x, start_y, 0, 0);
        } else {
            // If the previous point was an off-curve point, add a quadratic bezier curve to close the shape
            stbtt_setvertex(path_vertices + vertex_count, '\x03', start_x, start_y, current_x, current_y);
        }
    } else {
        // If the starting point was an off-curve point
        if (prev_was_off_curve != 0) {
            // If the previous point was also an off-curve point, add a quadratic bezier curve to the midpoint
            stbtt_setvertex(path_vertices + vertex_count, '\x03', (current_x + start_control_x) >> 1, (current_y + start_control_y) >> 1, current_x, current_y);
            vertex_count++;
        }
        // Add a quadratic bezier curve to the starting point
        stbtt_setvertex(path_vertices + vertex_count, '\x03', start_x, start_y, start_control_x, start_control_y);
    }
    // Return the updated number of vertices
    return vertex_count + 1;
}