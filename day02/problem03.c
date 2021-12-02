#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 11
#define UP_OFFSET 3
#define DOWN_OFFSET 5
#define FORWARD_OFFSET 8

int main(void)
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open input.\n");
        return 1;
    }

    char line[LINE_SIZE];
    int x = 0;
    int y = 0;

    while (fgets(line, sizeof(line), input))
    {
        // Assuming the input is good we only need to check the first letter
        switch (line[0])
        {
            case 'u':
                y -= atoi(line + UP_OFFSET);
                break;
            case 'd':
                y += atoi(line + DOWN_OFFSET);
                break;
            case 'f':
                x += atoi(line + FORWARD_OFFSET);
                break;
            default:
                fprintf(stderr, "Bad input.\n");
                break;
        }
    }

    printf("%i\n", x * y);
}