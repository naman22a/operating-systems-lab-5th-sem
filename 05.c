#include <stdio.h>
#define MAX 10

void firstFit(int partitions[], int pCount, int processes[], int prCount)
{
    int allocation[MAX];
    for (int i = 0; i < prCount; i++)
        allocation[i] = -1;

    for (int i = 0; i < prCount; i++)
    {
        for (int j = 0; j < pCount; j++)
        {
            if (partitions[j] >= processes[i])
            {
                allocation[i] = j;
                partitions[j] -= processes[i];
                break;
            }
        }
    }

    printf("\n--- First Fit ---\n");
    for (int i = 0; i < prCount; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d (Size %d) -> Partition %d\n", i + 1, processes[i], allocation[i] + 1);
        else
            printf("Process %d (Size %d) -> Not Allocated\n", i + 1, processes[i]);
    }
}

void bestFit(int partitions[], int pCount, int processes[], int prCount)
{
    int allocation[MAX];
    for (int i = 0; i < prCount; i++)
        allocation[i] = -1;

    for (int i = 0; i < prCount; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < pCount; j++)
        {
            if (partitions[j] >= processes[i])
            {
                if (bestIdx == -1 || partitions[j] < partitions[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            partitions[bestIdx] -= processes[i];
        }
    }

    printf("\n--- Best Fit ---\n");
    for (int i = 0; i < prCount; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d (Size %d) -> Partition %d\n", i + 1, processes[i], allocation[i] + 1);
        else
            printf("Process %d (Size %d) -> Not Allocated\n", i + 1, processes[i]);
    }
}

void worstFit(int partitions[], int pCount, int processes[], int prCount)
{
    int allocation[MAX];
    for (int i = 0; i < prCount; i++)
        allocation[i] = -1;

    for (int i = 0; i < prCount; i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < pCount; j++)
        {
            if (partitions[j] >= processes[i])
            {
                if (worstIdx == -1 || partitions[j] > partitions[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            partitions[worstIdx] -= processes[i];
        }
    }

    printf("\n--- Worst Fit ---\n");
    for (int i = 0; i < prCount; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d (Size %d) -> Partition %d\n", i + 1, processes[i], allocation[i] + 1);
        else
            printf("Process %d (Size %d) -> Not Allocated\n", i + 1, processes[i]);
    }
}

int main()
{
    int partitions[MAX], processes[MAX];
    int pCount, prCount;

    printf("Enter number of partitions: ");
    scanf("%d", &pCount);
    printf("Enter sizes of partitions:\n");
    for (int i = 0; i < pCount; i++)
        scanf("%d", &partitions[i]);

    printf("Enter number of processes: ");
    scanf("%d", &prCount);
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < prCount; i++)
        scanf("%d", &processes[i]);

    int p1[MAX], p2[MAX], p3[MAX];
    for (int i = 0; i < pCount; i++)
    {
        p1[i] = partitions[i];
        p2[i] = partitions[i];
        p3[i] = partitions[i];
    }

    firstFit(p1, pCount, processes, prCount);
    bestFit(p2, pCount, processes, prCount);
    worstFit(p3, pCount, processes, prCount);

    return 0;
}
