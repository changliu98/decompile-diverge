void __cdecl func0(const char *class_name, const char **extensions, int ext_count, char *output)
{
    const char *strongest = NULL;
    int max_strength = -1000;

    // Find the extension with the highest "strength"
    for (int i = 0; i < ext_count; ++i)
    {
        const char *extension = extensions[i];
        int strength = 0;

        // Calculate strength: +1 for uppercase letters, -1 for lowercase letters
        for (int j = 0; extension[j] != '\0'; ++j)
        {
            char chr = extension[j];
            if (chr >= 'A' && chr <= 'Z')
                ++strength;
            else if (chr >= 'a' && chr <= 'z')
                --strength;
        }

        // Update the strongest extension if the current one has a higher score
        if (strength > max_strength)
        {
            max_strength = strength;
            strongest = extension;
        }
    }

    // Write the result in "ClassName.strongest_extension" format
    sprintf(output, "%s.%s", class_name, strongest);
}