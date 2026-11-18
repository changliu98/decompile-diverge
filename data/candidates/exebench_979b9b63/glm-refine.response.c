int __cdecl openI2CBus(int *bus, const char *device)
{
    // open() with O_RDWR (2) opens the device for both reading and writing
    *bus = open(device, O_RDWR);
    
    // Returns a boolean value: true (1) if an error occurred, false (0) on success
    return *bus < 0;
}