#include <stdio.h>

#define LINE_SIZE 14
#define LINE_COUNT 1000
#define DIGITS_COUNT 12

int power_of_two(int n)
{
    int result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= 2;
    }
    return result;
}

int main(void)
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open input.\n");
        return 1;
    }

    // This array stores the number of times each digit was equal to '1'
    int unit_count[DIGITS_COUNT] = { 0 };
    char line[LINE_SIZE];
    
    while (fgets(line, sizeof(line), input))
    {
        for (int i = 0; i < DIGITS_COUNT; i++)
        {
            if (line[i] == '1')
            {
                unit_count[i]++;
            }
        }
    }

    int epsilon = 0;
    int gamma = 0;
    for (int i = 0; i < DIGITS_COUNT; i++)
    {
        if (unit_count[i] > LINE_COUNT / 2)
        {
            gamma += power_of_two(DIGITS_COUNT - i - 1);
        }
        else
        {
            epsilon += power_of_two(DIGITS_COUNT - i - 1);
        }
    }
    printf("epsilon: %i\t gamma: %i\t result: %i\n", epsilon, gamma, epsilon * gamma);
}