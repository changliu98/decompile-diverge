double _glfwPlatformGetTime(_GLFWwindow* window)
{
    double result;
# 158 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/DavidMutchler/kiss/refs/heads/master/external/glfw/lib/x11/x11_time.c"
    window->x11.time += ((unsigned long) 1103515245 * window->x11.time + 12345);

    result = (double) (window->x11.time & 0x7fff) / 32767.0;


    return result;
}