void par_shapes_compute_normals(par_shapes_mesh* m) {
    // Free existing normals if they exist
    if (m->normals) {
        par_shapes__free(m->normals);
    }
    
    // Allocate new normals array (3 floats per point)
    m->normals = (float*)par_shapes__malloc((unsigned long)m->npoints * 3 * sizeof(float));
    
    // Initialize all normals to {0, 0, 0}
    float* normals_ptr = m->normals;
    for (int i = 0; i < m->npoints; i++) {
        par_shapes__copy3(normals_ptr, (float[]){0, 0, 0});
        normals_ptr += 3;
    }
    
    // Accumulate face normals for each vertex
    for (int i = 0; i < m->ntriangles; i++) {
        uint16_t* triangle = (uint16_t*)m->triangles + i * 3;
        
        float* a = m->points + (size_t)triangle[0] * 3;
        float* b = m->points + (size_t)triangle[1] * 3;
        float* c = m->points + (size_t)triangle[2] * 3;
        
        float ab[3], ac[3], n[3];
        
        // Compute edge vectors
        par_shapes__subtract3(ab, b, a);
        par_shapes__subtract3(ac, c, a);
        
        // Compute face normal via cross product
        par_shapes__cross3(n, ab, ac);
        
        // Accumulate normal to each vertex of the triangle
        par_shapes__copy3(ab, n);
        par_shapes__copy3(m->normals + (size_t)triangle[0] * 3, ab);
        
        par_shapes__copy3(ab, n);
        par_shapes__copy3(m->normals + (size_t)triangle[1] * 3, ab);
        
        par_shapes__copy3(ab, n);
        par_shapes__copy3(m->normals + (size_t)triangle[2] * 3, ab);
    }
    
    // Normalize all accumulated vertex normals
    float* n_ptr = m->normals;
    for (int i = 0; i < m->npoints; i++) {
        par_shapes__normalize3(n_ptr);
        n_ptr += 3;
    }
}