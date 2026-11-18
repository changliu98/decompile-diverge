void calcula_target(int *obstacle, int *agent, int *reflection_point)
{
    // Calculate the x-coordinate of the target by mirroring pacman's position relative to red
    *reflection_point = (*agent - *obstacle) + *agent;
    // Calculate the y-coordinate of the target by mirroring pacman's position relative to red
    reflection_point[1] = (agent[1] - obstacle[1]) + agent[1];
}