#include <stdio.h>

int main() {
    int x = -16;  // Binary representation: 1111 0000

    // Logical right shift by 2 positions
    int result = (unsigned)x >> 16;  // Cast to unsigned before the shift

    printf("Original number: %d\n", x);
    printf("Result after logical right shift: %d\n", result);

    return 0;
}