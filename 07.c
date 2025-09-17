#include <stdio.h>
#include <stdbool.h>

int main()
{
    int P, R;

    printf("Enter the number of processes: ");
    scanf("%d", &P);

    printf("Enter the number of resources: ");
    scanf("%d", &R);

    int processes[P];
    for (int i = 0; i < P; i++)
        processes[i] = i;

    int max[P][R], allot[P][R], need[P][R], avail[R];

    printf("\nEnter Allocation Matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allot[i][j]);

    printf("\nEnter Max Matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources (%d):\n", R);
    for (int i = 0; i < R; i++)
        scanf("%d", &avail[i]);

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    bool finish[P];
    for (int i = 0; i < P; i++)
        finish[i] = false;

    int safeSeq[P], work[R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0;

    while (count < P)
    {
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            if (!finish[p])
            {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R)
                {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found)
        {
            printf("\nSystem is not in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}
