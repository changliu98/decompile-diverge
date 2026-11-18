void rotate_point(struct Point3D *p) {
    // These constants are loaded from memory.
    // Based on the math, they correspond to the sine and cosine 
    // of two fixed rotation angles (theta and phi).
    // E.g., cos_theta = 0.866025f, sin_theta = 0.5f, 
    // cos_phi = 0.707107f, sin_phi = 0.707107f
    float cos_theta = 0.866025f; // -0x18(%rbp)
    float sin_theta = 0.5f;      // -0x1c(%rbp)
    float cos_phi   = 0.707107f; // -0x20(%rbp)
    float sin_phi   = 0.707107f; // -0x24(%rbp)

    float x = p->x; // -0x14(%rbp)

    // Rotate around Z-axis
    // The `xor $0x80000000, %eax` instruction is equivalent to negating a float.
    float new_y = p->x * cos_theta + (-p->z * sin_theta); // -0x10(%rbp)
    float new_z = p->y * sin_theta + p->z * cos_theta;   // -0xc(%rbp)

    // Rotate around Y-axis
    p->x = x * cos_phi + (-new_z * sin_phi);
    p->y = new_y;
    p->z = x * sin_phi + new_z * cos_phi;
}