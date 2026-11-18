void passByPointer(int *ptr) {
    *ptr = 4;
    *ptr = *ptr << 2; // This is equivalent to *ptr *= 4;
}