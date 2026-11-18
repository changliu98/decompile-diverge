// Converts an endpoint index to an endpoint number and direction.
// The endpoint index is mapped to an endpoint number (0, 1, 2, ...)
// and the direction (0 for OUT, 1 for IN).
//
// Parameters:
//   epindex - The endpoint index to convert.
//   epdir   - Pointer to store the endpoint direction (0 for OUT, 1 for IN).
//             If NULL, the direction is not stored.
//
// Returns:
//   The endpoint number corresponding to the given endpoint index.
int epindex_to_epnum(int endpoint_index, int *endpoint_direction)
{
    // If the direction pointer is valid, calculate and store the direction.
    // The direction is determined by the least significant bit of the endpoint index.
    if (endpoint_direction) {
        *endpoint_direction = endpoint_index % 2;
    }
    // Calculate the endpoint number by dividing the endpoint index by 2.
    // This effectively maps pairs of indices (0,1), (2,3), etc., to the same endpoint number.
    return (endpoint_index + endpoint_index % 2) / 2;
}