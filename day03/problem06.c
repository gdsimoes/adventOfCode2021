#include <stdio.h>

#define LINE_SIZE 14
#define LINE_COUNT 1000
#define DIGIT_COUNT 12

char lines[LINE_COUNT][LINE_SIZE];
int oxygen_array[LINE_COUNT] = { -1 };

void oxygen(int digit);
void co2(int digit);
int power_of_two(int n);
int bintoi(char binary[]);

int main(void)
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open input.\n");
        return 1;
    }

    // Populate lines matrix
    for (int i = 0; i < LINE_COUNT; i++)
    {
        fgets(lines[i], sizeof(lines[i]), input);
    }

    // int oxygen_rating;
    oxygen(0);
    for (int i = 1; i < DIGIT_COUNT && oxygen_array[1] != -1; i++)
    {
        // printf("BEGIN\n");
        // for (int j = 0; oxygen_array[j] != -1; j++)
        // {
        //     printf("%s", lines[oxygen_array[j]]);
        // }
        // printf("END\n");
        oxygen(i);
    }

    printf("%i\n", bintoi(lines[oxygen_array[0]]));

    co2(0);
    for (int i = 1; i < DIGIT_COUNT && oxygen_array[1] != -1; i++)
    {
        // printf("BEGIN\n");
        // for (int j = 0; oxygen_array[j] != -1; j++)
        // {
        //     printf("%s", lines[oxygen_array[j]]);
        // }
        // printf("END\n");
        co2(i);
    }

    printf("%i\n", bintoi(lines[oxygen_array[0]]));
}

void oxygen(int digit)
{
    int unit_count = 0;
    int index = 0;
    char bitmost;

    if (digit == 0)
    {
        for (int i = 0; i < LINE_COUNT; i++)
        {
            if (lines[i][0] == '1')
            {
                unit_count++;
            }
        }

        bitmost = (unit_count >= LINE_COUNT / 2.0) ? '1' : '0';

        for (int i = 0; i < LINE_COUNT; i++)
        {
            if (lines[i][digit] == bitmost)
            {
                oxygen_array[index] = i;
                index++;
            }
        }
        oxygen_array[index] = -1;
        return;
    }

    int length;
    for (int i = 0; oxygen_array[i] != -1; i++)
    {
        if (lines[oxygen_array[i]][digit] == '1')
        {
            unit_count++;
        }
        length = i;
    }
    length++;
    // printf("length: %i\n", length);

    bitmost = (unit_count >= length / 2.0) ? '1' : '0';

    for (int i = 0; oxygen_array[i] != -1; i++)
    {
        if (lines[oxygen_array[i]][digit] == bitmost)
        {
            oxygen_array[index] = oxygen_array[i];
            index++;
        }
    }
    oxygen_array[index] = -1;
}

void co2(int digit)
{
    int unit_count = 0;
    int index = 0;
    char bitmost;

    if (digit == 0)
    {
        for (int i = 0; i < LINE_COUNT; i++)
        {
            if (lines[i][0] == '1')
            {
                unit_count++;
            }
        }

        bitmost = (unit_count >= LINE_COUNT / 2.0) ? '0' : '1';

        for (int i = 0; i < LINE_COUNT; i++)
        {
            if (lines[i][digit] == bitmost)
            {
                oxygen_array[index] = i;
                index++;
            }
        }
        oxygen_array[index] = -1;
        return;
    }

    int length;
    for (int i = 0; oxygen_array[i] != -1; i++)
    {
        if (lines[oxygen_array[i]][digit] == '1')
        {
            unit_count++;
        }
        length = i;
    }
    length++;
    // printf("length: %i\n", length);

    bitmost = (unit_count >= length / 2.0) ? '0' : '1';

    for (int i = 0; oxygen_array[i] != -1; i++)
    {
        if (lines[oxygen_array[i]][digit] == bitmost)
        {
            oxygen_array[index] = oxygen_array[i];
            index++;
        }
    }
    oxygen_array[index] = -1;
}

int power_of_two(int n)
{
    int result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= 2;
    }
    return result;
}

int bintoi(char binary[])
{
    int result = 0;
    for (int i = 0; i < DIGIT_COUNT; i++)
    {
        if (binary[i] == '1')
        {
            result += power_of_two(DIGIT_COUNT - i - 1);
        }
    }
    return result;
}