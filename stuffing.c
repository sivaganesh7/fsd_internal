#include <stdio.h>
#include <string.h>

int main() {
    char data[50], stuffed[100] = "";
    char start, end;
    int i, k = 0;

    // --- Input Section ---
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);       // read full line (with spaces)
    data[strcspn(data, "\n")] = '\0';       // remove newline at end

    printf("Enter start delimiter: ");
    scanf(" %c", &start);                   // note the space before %c
    printf("Enter end delimiter: ");
    scanf(" %c", &end);

    // --- Stuffing Section ---
    stuffed[k++] = start;                   // add start delimiter first

    for (i = 0; i < strlen(data); i++) {
        if (data[i] == start || data[i] == end)
            stuffed[k++] = data[i];         // duplicate if matches delimiter
        stuffed[k++] = data[i];
    }

    stuffed[k++] = end;                     // add end delimiter
    stuffed[k] = '\0';                      // terminate string

    printf("\nStuffed Data: %s\n", stuffed);

    return 0;
}
