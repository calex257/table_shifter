#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nth_bit_is_on(int number, int index)
{
    return (number & (1 <<index)) != 0;
}

void set_nth_bit_on(int *number, int index)
{
    (*number)=(*number)|(1<<index);
}

int main(int argc, char* argv[])
{
    //input is for the initial table state
    //transformed is for the final state which will be outputted
    //order is the new layout of the variables in the final table
    int n;
    printf("Enter the number of variables: ");
    scanf("%d", &n);
    char input[16], transformed[16] = { 0 }, order[5];
    for (int i = 0;i < 16;i++) {
        for (int j = 0;j < 4;j++) {
            //displays each line of the table
            //with the corresponding values of the variables
            printf("%c: %d | ", "ABCD"[j], nth_bit_is_on(i, 3-j));
        }
        //get the first character of the input for each line
        //ignoring the rest and preventing misinputs
        input[i]=fgetc(stdin);
        while (getchar() != '\n');
    }

    fgets(order, 5, stdin);
    strupr(order);
    for (int i = 0;i < 4;i++) {
        order[i] = 3 - order[i] + 'A';
    }
    for (int i = 0;i < 16;i++) {
        int index = 0;
        for (int j = 0;j < 4;j++) {
            if (nth_bit_is_on(i, 3-j)) {
                set_nth_bit_on(&index, order[j]);
            }
        }
        transformed[i] = input[index];
    }
    for (int i = 0;i < 16;i++)     {
        for (int j = 0;j < 4;j++) {
            printf("%c: %d | ", 3 - order[j] + 'A', nth_bit_is_on(i, 3-j));
        }
        printf("%c\n", transformed[i]);
    }
    return 0;
}