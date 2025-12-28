#ifdef EXPENSE_H
#define EXPENSE_H

#define MAX_DESCRIPTION_LENGTH 1000
#define MAX_DATE_LENGTH 11

typedef struct {
    char date[MAX_DATE_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    float amount;
} Expense;

#endif // EXPENSE_H