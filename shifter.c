#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nth_bit_is_on(int number, int index)
{
    return (number & (1 << index)) != 0;
}

void set_nth_bit_on(int* number, int index)
{
    (*number) = (*number) | (1 << index);
}

//check if the input is correct
void verify_input(char* order, char* var_names, int length)
{
    int wrong;
    do {
        wrong = 0;
        printf("Enter the new order of the variables\n(without spaces in between)\n");
        fgets(order, length + 1, stdin);
        if (strlen(order) != strlen(var_names)) {
            wrong = 1;
        }
        for (int i = 0;i < length && !wrong;i++) {
            if (!strchr(var_names, order[i])) {
                wrong = 1;
            }
        }
        if (wrong) {
            printf("Error. Invalid input\n");
        }
        getchar();
    } while (wrong);
}

int main(void)
{
    int var_number, values_number;
    char* input, * transformed, * order, * var_names;

    //input is for the initial table state
    //transformed is for the final state which will be outputted

    printf("Enter the number of variables: ");
    scanf("%d", &var_number);
    getchar();
    values_number = 1 << var_number;

    //allocate necessary space
    var_names = (char*)malloc(var_number * sizeof(char));
    order = (char*)malloc(var_number * sizeof(char));
    input = (char*)malloc(values_number * sizeof(char));
    transformed = (char*)malloc(values_number * sizeof(char));

    //receive labels for variables
    printf("Enter the names of the variables\n(without spaces in between)\n");
    fgets(var_names, var_number + 1, stdin);
    getchar();
    for (int i = 0;i < values_number;i++) {
        for (int j = 0;j < var_number;j++) {
            //displays each line of the table
            //with the corresponding values of the variables
            printf("%c: %d | ", var_names[j], nth_bit_is_on(i, var_number - 1 - j));
        }
        //get the first character of the input for each line
        //ignoring the rest and preventing misinputs
        input[i] = fgetc(stdin);
        while (getchar() != '\n');
    }

    //receive user order
    verify_input(order, var_names, var_number);

    //reorder the values and store them in transformed
    for (int i = 0;i < values_number;i++) {
        //start with a null index(all bits set to 0)
        int index = 0;
        for (int j = 0;j < var_number;j++) {
            //calculate new index based on previous index
            if (nth_bit_is_on(i, var_number - 1 - j)) {
                int pos;
                for (int k = 0;k < var_number;k++) {
                    if (order[j] == var_names[k]) {
                        pos = k;
                    }
                }
                set_nth_bit_on(&index, var_number - 1 - pos);
            }
        }
        transformed[i] = input[index];
    }
    for (int i = 0;i < values_number;i++) {
        for (int j = 0;j < var_number;j++) {
            //displays each line of the table
            //with the corresponding values of the variables
            printf("%c: %d | ", order[j], nth_bit_is_on(i, var_number - 1 - j));
        }
        printf("%c\n", transformed[i]);
    }

    //free allocated memory
    free(input);
    free(order);
    free(transformed);
    free(var_names);
    return 0;
}