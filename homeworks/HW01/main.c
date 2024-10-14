#include <stdio.h>
#include <math.h>

int main(void)
{
    char percent = '%', separator;
    int i = 0, day, prev_day = 0, input;
    double balance = 0, interest, debit, interest_rate, transaction, prev_transaction = 0;

    printf("Zadejte kreditni urok [%c]:\n", percent);
    if (scanf("%lf", &interest) != 1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte debetni urok [%c]:\n", percent);
    if (scanf("%lf", &debit) != 1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    interest = interest / 100;
    debit = debit / 100;

    printf("Zadejte transakce:\n");
    do
    {
        input = scanf("%d %c %lf", &day, &separator, &transaction);
        if (day < 0 || separator != ',' || ((i > 0) && (day <= prev_day)))
        {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if (day > 0)
        {
            for (int j = 0; j < (day - prev_day); j++)
            {
                if (prev_transaction > 0)
                {
                    interest_rate = (double)(floor((prev_transaction * interest) * 100) / 100);
                    prev_transaction = prev_transaction + interest_rate;
                }
                else
                {
                    interest_rate = (-1.0) * (double)(floor((fabs(prev_transaction) * debit) * 100) / 100);
                    prev_transaction = (prev_transaction + interest_rate);
                }
            }
        }

        balance = prev_transaction;

        if (transaction == 0)
        {
            printf("Zustatek: %.2lf\n", balance);
            break;
        }

        prev_day = day;
        prev_transaction = (transaction > 0) ? (balance + transaction) : (balance - fabs(transaction));
        i++;
    } while (input == 3);

    return 0;
}