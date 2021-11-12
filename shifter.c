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

int main(int argc, char* argv[])
{
    int var_number, values_number;
    char* input, * transformed, * order, * var_names, min_var_name;

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
    printf("Enter the names of the variables\n(without spaces in between)\n"
        "permutations of consecutive letters of the alphabet only\n");
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
    printf("Enter the new order of the variables\n(without spaces in between)\n");
    fgets(order, var_number + 1, stdin);
    //ensure the format is uniform
    strupr(order);

    //determine smallest value
    min_var_name = var_names[0];
    for (int i = 1;i < var_number;i++) {
        if (var_names[i] < min_var_name) {
            min_var_name = var_names[i];
        }
    }

    //modify order for indices
    for (int i = 0;i < var_number;i++) {
        order[i] = var_number - 1 - order[i] + min_var_name;
    }

    //reorder the values and store them in transformed
    for (int i = 0;i < values_number;i++) {
        //start with a null index(all bits set to 0)
        int index = 0;
        for (int j = 0;j < var_number;j++) {
            //calculate new index based on previous index
            if (nth_bit_is_on(i, var_number - 1 - j)) {
                set_nth_bit_on(&index, order[j]);
            }
        }
        transformed[i] = input[index];
    }
    for (int i = 0;i < values_number;i++) {
        for (int j = 0;j < var_number;j++) {
            //displays each line of the table
            //with the corresponding values of the variables
            printf("%c: %d | ", var_number - 1 - order[j] + min_var_name, nth_bit_is_on(i, var_number - 1 - j));
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