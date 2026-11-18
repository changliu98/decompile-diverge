int __cdecl sortedarray_insert(SortedArray *sortedarray, SortedArrayValue data)
{
    unsigned int left, right, index;
    SortedArrayValue *new_data;
    unsigned int new_size;

    if (sortedarray == NULL)
        return 0;

    // Binary search to find the insertion point
    left = 0;
    right = (sortedarray->length <= 1) ? 0 : sortedarray->length;
    index = 0;

    while (left != right)
    {
        index = (left + right) / 2;
        int order = sortedarray->cmp_func(data, sortedarray->data[index]);

        if (order == 0)
        {
            break; // Exact match found
        }
        else if (order > 0)
        {
            left = index + 1;
        }
        else
        {
            right = index;
        }
    }

    // If the loop finished without an exact match, `left` is the insertion index.
    // However, if the item at `index` is strictly smaller, we insert after it.
    if (sortedarray->length > 0 && sortedarray->cmp_func(data, sortedarray->data[index]) > 0)
    {
        index++;
    }

    // Resize the array if necessary (doubling the capacity)
    if (sortedarray->length + 1 > sortedarray->_alloced)
    {
        new_size = sortedarray->_alloced * 2;
        new_data = (SortedArrayValue *)realloc(sortedarray->data, sizeof(SortedArrayValue) * new_size);
        
        if (new_data == NULL)
            return 0;

        sortedarray->data = new_data;
        sortedarray->_alloced = new_size;
    }

    // Shift elements to the right to make space for the new element
    memmove(&sortedarray->data[index + 1], 
            &sortedarray->data[index], 
            sizeof(SortedArrayValue) * (sortedarray->length - index));

    // Insert the new element and update the length
    sortedarray->data[index] = data;
    sortedarray->length++;

    return 1;
}