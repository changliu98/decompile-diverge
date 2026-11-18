// Clips the rectangle defined by (*x, *y) to (*x2, *y2) against the clip rectangle (cx, cy) to (cx2, cy2).
// Updates *x, *y, *x2, *y2 in place to reflect the clipped rectangle.
// Returns 1 if the resulting rectangle is valid (i.e., width > 0 and height > 0), 0 otherwise.
char sraClipRect2(int *rect_left, int *rect_top, int *rect_right, int *rect_bottom, int clip_left, int clip_top, int clip_right, int clip_bottom)
{
    // Clamp the top-left x coordinate to be at least cx
    if (*rect_left < clip_left) *rect_left = clip_left;
    // Clamp the top-left y coordinate to be at least cy
    if (*rect_top < clip_top) *rect_top = clip_top;
    // If the clipped left edge is at or beyond the clip right edge, move it one pixel left
    if (clip_right <= *rect_left) *rect_left = clip_right - 1;
    // If the clipped top edge is at or beyond the clip bottom edge, move it one pixel up
    if (clip_bottom <= *rect_top) *rect_top = clip_bottom - 1;
    // If the original right edge is at or before the clip left edge, move it one pixel right
    if (*rect_right <= clip_left) *rect_right = clip_left + 1;
    // If the original bottom edge is at or before the clip top edge, move it one pixel down
    if (*rect_bottom <= clip_top) *rect_bottom = clip_top + 1;
    // Clamp the bottom-right x coordinate to be at most cx2
    if (clip_right < *rect_right) *rect_right = clip_right;
    // Clamp the bottom-right y coordinate to be at most cy2
    if (clip_bottom < *rect_bottom) *rect_bottom = clip_bottom;
    // Return true if the resulting rectangle has positive width and height
    return (*rect_left < *rect_right) && (*rect_top < *rect_bottom);
}