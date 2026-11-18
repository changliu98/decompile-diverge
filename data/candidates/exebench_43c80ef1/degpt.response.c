/**
 * @brief Extracts face index and vertex index from a combined index.
 *
 * The lower 2 bits of iIndexIn represent the vertex index (0-3).
 * The remaining higher bits represent the face index.
 *
 * @param piFace Pointer to store the extracted face index.
 * @param piVert Pointer to store the extracted vertex index.
 * @param iIndexIn The combined index value.
 */
void IndexToData(int *faceIndex,int *vertexIndex,int combinedIndex)
{
  // Extract the vertex index from the lower 2 bits
  *vertexIndex = combinedIndex & 3;
  // Extract the face index by shifting right by 2 bits
  *faceIndex = combinedIndex >> 2;
}