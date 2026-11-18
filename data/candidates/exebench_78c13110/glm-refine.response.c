void __cdecl MotionToFrameCoord(int block_y, int block_x, int motion_y, int motion_x, int *out_y, int *out_x)
{
    // Convert 8x8 block coordinates to frame coordinates by adding the motion vector offset
    *out_y = motion_y + (8 * block_y);
    *out_x = motion_x + (8 * block_x);
}