void find_next_cell(int *grid_size, int *pos, int *directions, double *velocities, int *new_pos) {
    int new_directions[3];
    bool out_of_bounds = true;
    
    for (int i = 0; i < 3; i++) {
        new_directions[i] = directions[i];
    }
    
    for (int i = 0; i < 3; i++) {
        new_pos[i] = pos[i];
    }
    
    for (int i = 0; i < 3; i++) {
        if (directions[i] == -1) {
            continue;
        } else if (directions[i] == 0) {
            if (velocities[0] > 0.0) {
                new_pos[0] = pos[0] - 1;
                new_directions[i] = 1;
                if (new_pos[0] < 0) {
                    out_of_bounds = true;
                    break;
                }
            }
        } else if (directions[i] == 1) {
            if (velocities[0] > 0.0) {
                new_pos[0] = pos[0] + 1;
                new_directions[i] = 0;
                if (new_pos[0] > grid_size[0] - 1) {
                    out_of_bounds = true;
                    break;
                }
            }
        } else if (directions[i] == 2) {
            if (velocities[1] > 0.0) {
                new_pos[1] = pos[1] - 1;
                new_directions[i] = 3;
                if (new_pos[1] < 0) {
                    out_of_bounds = true;
                    break;
                }
            }
        } else if (directions[i] == 3) {
            if (velocities[1] > 0.0) {
                new_pos[1] = pos[1] + 1;
                new_directions[i] = 2;
                if (new_pos[1] > grid_size[1] - 1) {
                    out_of_bounds = true;
                    break;
                }
            }
        } else if (directions[i] == 4) {
            if (velocities[2] > 0.0) {
                new_pos[2] = pos[2] - 1;
                new_directions[i] = 5;
                if (new_pos[2] < 0) {
                    out_of_bounds = true;
                    break;
                }
            }
        } else if (directions[i] == 5) {
            if (velocities[2] > 0.0) {
                new_pos[2] = pos[2] + 1;
                new_directions[i] = 4;
                if (new_pos[2] > grid_size[2] - 1) {
                    out_of_bounds = true;
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < 3; i++) {
        directions[i] = new_directions[i];
    }
}