void __cdecl IndexToData(int *outFace, int *outVert, const int index)
{
  *outVert = index & 3;   // Extract the 2 least significant bits for the vertex
  *outFace = index >> 2;  // Extract the remaining bits for the face
}