int binary_heap_insert(BinaryHeap *heap,BinaryHeapValue value)

{
  uint uVar1;
  int iVar2;
  BinaryHeapValue *ppvVar3;
  uint parent;
  uint new_size;
  uint index;
  BinaryHeapValue *new_values;
  BinaryHeapValue value_local;
  BinaryHeap *heap_local;
  
  if (heap->alloced_size <= heap->num_values) {
    uVar1 = heap->alloced_size << 1;
    ppvVar3 = realloc(heap->values,(ulong)uVar1 << 3);
    if (ppvVar3 == (BinaryHeapValue *)0x0) {
      return 0;
    }
    heap->alloced_size = uVar1;
    heap->values = ppvVar3;
  }
  index = heap->num_values;
  heap->num_values = heap->num_values + 1;
  while (index != 0) {
    uVar1 = index - 1 >> 1;
    iVar2 = binary_heap_cmp(heap,heap->values[uVar1],value);
    if (iVar2 < 0) break;
    heap->values[index] = heap->values[uVar1];
    index = uVar1;
  }
  heap->values[index] = value;
  return 1;
}