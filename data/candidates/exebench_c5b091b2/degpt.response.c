// Calculates the intersection fraction of a line segment with a plane at zc.
// Returns 1 if the segment [z0, z1] intersects the plane zc, 0 otherwise.
// If intersection occurs, stores the barycentric coordinate (fraction along the segment) in *f.
int ctr_intersect(double z_start, double z_end, double z_plane, double *fraction)
{
    // Check if zc lies strictly between z0 and z1 (i.e., the segment crosses the plane)
    bool intersects = (z_start - z_plane) * (z_end - z_plane) < 0.0;
    if (intersects) {
        // Compute the fraction along the segment where the intersection occurs
        *fraction = (z_plane - z_start) / (z_end - z_start);
    }
    // Return 1 if intersection exists, 0 otherwise
    return (int)intersects;
}