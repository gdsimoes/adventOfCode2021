#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_SIZE 300
#define DIMENSION 5

typedef struct node
{
    int board[DIMENSION][DIMENSION];
    bool marked[DIMENSION][DIMENSION];
    bool won;
    struct node *next;
}
node;


FILE *input;
char line[LINE_SIZE];
int draw[LINE_SIZE];
int draw_length;
node *boards;

int populate_array(int arr[], char separator);
void print_node(node *n);
void populate_boards(void);
bool mark(int number);
bool check(node *n, int a, int b);

int main(void)
{
    // Open input file
    input = fopen("input", "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open input.\n");
        return 1;
    }

    // Populate draw array
    fgets(line, sizeof(line), input);
    draw_length = populate_array(draw, ',');

    // Print all numbers in the draw array
    // for (int i = 0; i < draw_length; i++)
    // {
    //     printf("%i ", draw[i]);
    // }
    // printf("\n");


    // Populate boards linked list
    populate_boards();

    // Mark all numbers and check if someone won
    for (int i = 0; i < draw_length; i++)
    {
        mark(draw[i]);
    }

}

int populate_array(int arr[], char separator)
{
    int size = 0;
    char numstr[3];         // In bingo we only have numbers with one or two digits

    for (int i = 0, ni = 0; line[i] != '\n'; i++)
    {
        // printf("i: %i\t ni: %i\t line[i]: %c\t size: %i\t arr[size]: %i\n", i, ni, line[i], size, arr[size-1]);
        // Check if line[i] is the separator and, if it is, save the previous number
        if (line[i] == separator)
        {
            // If there is a number
            if (ni > 0)
            {
                arr[size] = atoi(numstr);
                ni = 0;
                size++;
            }
        }
        else
        {
            // Save digit to numstr
            numstr[ni] = line[i];
            numstr[ni + 1] = '\0';
            ni++;
        }
    }

    // We need to save the last number in the array
    arr[size] = atoi(numstr);
    size++;

    // for(int i = 0; i < size; i++)
    // {
    //     printf("size: %i\tarr[%i]: %i\n", size, i, arr[i]);
    // }

    return size;
}

// This is for debugging purposes
void print_node(node *n)
{
    for (int i = 0; i < DIMENSION; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            printf("%i ", n->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void populate_boards(void)
{
    while (fgets(line, sizeof(line), input) != NULL)
    {
        node *n = calloc(1, sizeof(node));

        for (int i = 0; i < DIMENSION; i++)
        {
            if (fgets(line, sizeof(line), input) == NULL)
            {
                free(n);
                return;
            }
            populate_array(n->board[i], ' ');
        }

        n->next = boards;
        boards = n;

        // print_node(n);
    }
}

bool mark(int number)
{
    bool result = false;
    for (node *tmp = boards; tmp != NULL; tmp = tmp->next)
    {
        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                if (number == tmp->board[i][j])
                {
                    tmp->marked[i][j] = true;
                    if (check(tmp, i, j))
                    {
                        result = true;
                    }
                }
            }
        }
    }
    return result;
}

bool check(node *n, int a, int b)
{
    bool won = true;
    for (int i = 0; i < DIMENSION; i++)
    {
        if (!n->marked[i][b])
        {
            won = false;
            break;
        }
    }

    if (!won)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            if (!n->marked[a][j])
            {
                return false;
            }
        }
    }

    // That means that player won and we can print the result
    int sum = 0;
    for (int i = 0; i < DIMENSION; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            if (!n->marked[i][j])
            {
                // printf("DEBUG: i: %i\t j: %i\t value: %i\t sum: %i\n", i, j, n->board[i][j], sum);
                sum += n->board[i][j];
            }
        }
    }
    if (!n->won)
    {
        n->won = true;
        printf("a: %i\t b: %i\t number: %i\t sum: %i\t sum * number: %i\n", a, b, n->board[a][b], sum, sum * n->board[a][b]);
    }


    return true;
}