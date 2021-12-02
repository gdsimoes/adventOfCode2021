#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 6
#define WINDOW_SIZE 3

int main(void)
{
    // Open input file
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open input.\n");
        return 1;
    }

    char line[LINE_SIZE];
    int window[WINDOW_SIZE];
    int count = 0;

    // Read the first few lines. I'm assuming the file is big enough.
    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        fgets(line, sizeof(line), input);
        window[i] = atoi(line);
    }

    // Read the rest of the file and count how many measurement windows are larger than the previous one
    int i = 0;
    while (fgets(line, sizeof(line), input))
    {
        int curr = atoi(line);
        if (curr > window[i])
        {
            count++;
        }
        // Here we wrap around the array to avoid any swapping of elements
        window[i] = curr;
        i = (i + 1) % WINDOW_SIZE;
    }

    // Print the result
    printf("%i\n", count);




}