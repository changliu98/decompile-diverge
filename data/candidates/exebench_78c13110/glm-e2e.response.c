void MotionToFrameCoord(int motion_x, int motion_y, int frame_x, int frame_y, int *out_x, int *out_y) {
    *out_x = (motion_x << 3) + frame_x;
    *out_y = (motion_y << 3) + frame_y;
}