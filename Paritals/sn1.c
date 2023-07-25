#include <stdlib.h>
#include <stdio.h>

int main() {
#ifdef _WIN32
    // Windows
    system("color 1B"); // 1 for light blue background, B for default text color
#else
    // Not supported for other platforms
    printf("Changing console background color is not supported on this platform.\n");
#endif

    printf("This is the console with a light blue background color.\n");

    return 0;
}
