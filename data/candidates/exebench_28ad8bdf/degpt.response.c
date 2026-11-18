void matrixApply(float *transformMatrix, float pointX, float pointY, float pointZ, float *resultX, float *resultY, float *resultZ)
{
    // Apply 4x4 transformation matrix (column-major order) to a 3D point (x, y, z)
    // m[0..3]   : first column (x-axis)
    // m[4..7]   : second column (y-axis)
    // m[8..11]  : third column (z-axis)
    // m[12..15] : fourth column (translation), though only m[3], m[7], m[11] are used here
    // Note: This implementation assumes the input vector is (x, y, z, 1) and extracts only the xyz components of the result.

    // Calculate transformed x coordinate
    *resultX = pointZ * transformMatrix[2] + pointX * *transformMatrix + pointY * transformMatrix[1] + transformMatrix[3];
    
    // Calculate transformed y coordinate
    *resultY = pointZ * transformMatrix[6] + pointX * transformMatrix[4] + pointY * transformMatrix[5] + transformMatrix[7];
    
    // Calculate transformed z coordinate
    *resultZ = pointZ * transformMatrix[10] + pointX * transformMatrix[8] + pointY * transformMatrix[9] + transformMatrix[11];
}