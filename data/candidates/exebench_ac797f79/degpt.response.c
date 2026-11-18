/**
 * Removes items from the room bag based on the specified item quantities.
 *
 * @param item     Pointer to an array containing the quantities of items to remove.
 * @param roomBag  Pointer to an array representing the current contents of the room bag.
 * @param nbDim    The number of dimensions (items) in the arrays.
 */
void addItemToBag(int *itemsToRemove, int *currentBagContents, int numItems)
{
  // Subtract each item quantity from the corresponding room bag entry
  for (int i = 0; i < numItems; i++) {
    currentBagContents[i] -= itemsToRemove[i];
  }
}