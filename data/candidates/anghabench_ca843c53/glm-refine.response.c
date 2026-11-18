int __cdecl maya_pb_route_shift(int idx)
{
    // Wrap the index to stay within the bounds of the 10-element array
    int wrapped_idx = idx % 10;
    
    return maya_pb_route_shift_shift[wrapped_idx];
}