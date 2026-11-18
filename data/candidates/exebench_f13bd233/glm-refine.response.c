Reconstructed function
void __cdecl mtxLoadTranslate(Matrix4x4 *mtx, float xTrans, float yTrans, float zTrans)
{
    // Initialize the main diagonal (Identity matrix basis)
    mtx->m[0][0] = 1.0f;
    mtx->m[1][1] = 1.0f;
    mtx->m[2][2] = 1.0f;
    mtx->m[3][3] = 1.0f;

    // Clear the off-diagonal elements
    mtx->m[0][1] = 0.0f;
    mtx->m[0][2] = 0.0f;
    mtx->m[0][3] = 0.0f;
    
    mtx->m[1][0] = 0.0f;
    mtx->m[1][2] = 0.0f;
    mtx->m[1][3] = 0.0f;
    
    mtx->m[2][0] = 0.0f;
    mtx->m[2][1] = 0.0f;
    mtx->m[2][3] = 0.0f;
    
    mtx->m[3][0] = 0.0f;
    mtx->m[3][1] = 0.0f;
    mtx->m[3][2] = 0.0f;

    // Set the translation vector
    // Note: In a flat array, indices 12, 13, 14 correspond to m[3][0], m[3][1], m[3][2]
    // This represents the translation column in a column-major matrix (e.g., OpenGL)
    mtx->m[3][0] = xTrans;
    mtx->m[3][1] = yTrans;
    mtx->m[3][2] = zTrans;
}