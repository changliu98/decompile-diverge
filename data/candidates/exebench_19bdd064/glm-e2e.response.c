void ComputeAndOrientation(float xmm0_in, Vec3 *in_vec, Vec3 *out_vec) {
    float local_x;
    float local_y;
    float temp;

    out_vec->x = xmm0_in;

    local_x = in_vec->x;
    local_y = in_vec->y;

    if (local_x < 0.0f) {
        local_x += 1.0f;
    }

    if (local_y < 0.0f) {
        local_y += 1.0f;
    }

    if (local_y > 0.0f && local_y <= 1.0f) {
        local_x -= 0.0f; // Likely an artifact of compiler optimization or a stripped operation
        if (local_x < 0.0f) {
            local_x += 1.0f;
        }
    }

    if (local_x >= 0.0f) {
        out_vec->y = -local_x;
    }

    if (local_x > 0.0f) {
        out_vec->y = 1.0f - local_x;
    }

    if (local_y >= 0.0f && local_y <= 0.0f) {
        out_vec->z = local_y;
    } else {
        if (local_y > 0.0f && local_y <= 1.0f) {
            out_vec->z = 0.0f - local_y;
        } else {
            out_vec->z = local_y - 1.0f;
        }
    }
}