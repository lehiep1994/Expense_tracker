// This is where i start to build my own expense tracker in C

#include <stdio.h>
#include <stdlib.h>


#include "../lib/Expense.h"



int main() {
    Expense exp;
    printf("Enter expense description: ");
    fgets(exp.description, sizeof(exp.description), stdin);
    printf("Enter expense amount: ");
    scanf("%f", &exp.amount);

    printf("Expense Recorded: %s - $%.2f\n", exp.description, exp.amount);
    return 0;
}
