#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 6

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
    int prev, curr;
    int count = 0;

    // Read the first line
    fgets(line, sizeof(line), input);
    prev = atoi(line);

    // Read the rest of the file and count how many measurements are larger than the previous one
    while (fgets(line, sizeof(line), input))
    {
        curr = atoi(line);
        if (curr > prev)
        {
            count++;
        }
        prev = curr;
    }

    // Print the result
    printf("%i\n", count);




}