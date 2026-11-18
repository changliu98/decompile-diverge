void __cdecl agrega(int *head, int *tail, int node_index, int *next)
{
    // If the list is empty, the new node becomes the head
    if (*head == -1)
    {
        *head = node_index;
    }
    // Otherwise, link the current tail to the new node
    else
    {
        next[*tail] = node_index;
    }
    
    // The new node becomes the tail, and its 'next' pointer is set to -1 (null)
    *tail = node_index;
    next[*tail] = -1;
}