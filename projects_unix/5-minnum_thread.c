#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Array struct
typedef struct array
{
    int size;
    long *part_vector;
} Vector;

// The function get array and return the min value int the array;
void *findMin(void *arg)
{
    Vector vec = *((Vector *)arg);
    if (vec.size <= 0)
        return (void *)0;

    long min = vec.part_vector[0];

    for (int i = 1; i < vec.size; i++)
    {
        if (vec.part_vector[i] < min)
            min = vec.part_vector[i];
    }
    return (void *)min;
}

int main(int argc, const char *argv[])
{

    long *main_array;
    Vector arr1;
    Vector arr2;

    if (argc <= 1)
    {
        fprintf(stderr, "You need to send argument'\n");
        return 1;
    }

    int size_main_array = argc - 1;
    main_array = (long *)malloc(size_main_array * sizeof(long));
    if (main_array == NULL)
    {
        perror("Allocation");
    }

    for (int i = 0; i < size_main_array; i++)
    {
        main_array[i] = atol(argv[i + 1]);
    }

    int size_array1 = size_main_array % 2 == 0 ? size_main_array / 2 : size_main_array / 2 + 1;
    int size_array2 = size_main_array / 2;

    pthread_t tid1, tid2;
    void *min1;
    void *min2;

    arr1.size = size_array1;
    arr1.part_vector = main_array;
    if (pthread_create(&tid1, NULL, findMin, &arr1))
        return 1;

    arr2.part_vector = main_array + arr1.size;
    arr2.size = size_array2;

    if (pthread_create(&tid2, NULL, findMin, &arr2))
        return 1;

    if (pthread_join(tid1, &min1))
    {
        fprintf(stderr, "Could not join first Thread\n");
        return 1;
    }

    if (pthread_join(tid2, &min2))
    {
        fprintf(stderr, "Could not join second Thread\n");
        return 1;
    }

    if (arr2.size == 0)
    {
        printf("Min = [%ld]\n", (long)min1);
    }
    else if ((long)min1 < (long)min2)
        printf("Min = [%ld]\n", (long)min1);
    else
        printf("Min = [%ld]\n", (long)min2);

    return 0;
}
