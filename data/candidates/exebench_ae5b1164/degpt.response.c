// Calculates the intersection fraction of a line segment (z0, z1) with a plane at zc.
// Returns 1 if an intersection exists, storing the fraction in *f.
// Returns 0 if no intersection exists (segment is entirely on one side of the plane,
// or both endpoints are exactly on the plane).
int ctr_intersect(double z_start, double z_end, double z_plane, double *intersection_fraction)
{
    // Check if both endpoints are on the same side of the plane, or both are exactly on the plane.
    // The condition ((z0 < zc) == (z1 < zc)) is true when both are less than zc or both are >= zc.
    // The additional checks handle the case where one or both endpoints are exactly equal to zc,
    // ensuring we don't count an intersection if both endpoints are at zc (and are not NaN).
    if (((z_start < z_plane) == (z_end < z_plane)) || ((z_start == z_plane && !is_nan(z_start) && !is_nan(z_plane))) || ((z_end == z_plane && !is_nan(z_end) && !is_nan(z_plane)))) {
        return 0;
    }
    // Calculate the fraction along the segment where the intersection occurs.
    *intersection_fraction = (z_plane - z_start) / (z_end - z_start);
    return 1;
}