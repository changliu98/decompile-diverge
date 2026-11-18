/**
 * @brief Converts motion vector coordinates to frame pixel coordinates.
 *
 * @param by Block Y coordinate in macroblock units.
 * @param bx Block X coordinate in macroblock units.
 * @param my Motion vector Y component (pixel offset within the block).
 * @param mx Motion vector X component (pixel offset within the block).
 * @param yP Pointer to store the resulting Y coordinate in frame pixels.
 * @param xP Pointer to store the resulting X coordinate in frame pixels.
 */
void MotionToFrameCoord(int blockY,int blockX,int mvY,int mvX,int *frameY,int *frameX)
{
  // Calculate frame Y coordinate: macroblock Y * 8 + pixel Y offset
  *frameY = blockY * 8 + mvY;
  // Calculate frame X coordinate: macroblock X * 8 + pixel X offset
  *frameX = blockX * 8 + mvX;
}