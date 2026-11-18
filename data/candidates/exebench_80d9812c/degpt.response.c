// Sets the leaf bit in the link pointer and returns the leaf status.
// The leaf bit is the least significant bit (LSB) of the pointer.
// This function masks out all bits except the LSB to isolate the leaf flag.
size_t bnode_link_set_leaf(size_t *link)
{
  // Retrieve the current value of the link pointer
  size_t current_link_value = *link;
  // Update the link pointer to retain only the leaf bit (LSB)
  *link = current_link_value & 1;
  // Return the leaf status (1 if leaf, 0 otherwise)
  return current_link_value & 1;
}