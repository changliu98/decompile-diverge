// Adds a new node with value i to the end of the linked list
// head: pointer to the head index of the list
// tail: pointer to the tail index of the list
// i: the value to be added
// ll: array representing the linked list nodes
void agrega(int *head_index, int *tail_index, int new_node_index, int *linked_list_array)
{
  // If the list is empty (head is -1)
  if (*head_index == -1) {
    // Set both head and tail to the new node index
    *head_index = new_node_index;
    *tail_index = new_node_index;
  }
  else {
    // Link the current tail to the new node
    linked_list_array[*tail_index] = new_node_index;
    // Update tail to point to the new node
    *tail_index = new_node_index;
  }
  // Mark the end of the new node with -1
  linked_list_array[*tail_index] = -1;
}