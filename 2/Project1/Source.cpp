#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    const int size = 100;
    double arr[size][size], barr[size];
    int n = 0, k = 0;
    errno_t err = 0;
    FILE* ar1;
    err = fopen_s(&ar1, "matrix.txt", "r");
    if (err != 0) {
        perror("to be continued. . .\n");
        return EXIT_FAILURE;
    }

    fscanf_s(ar1, "%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf_s(ar1, "%lf", &arr[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        fscanf_s(ar1, "%lf\n", &arr[i][k]);
    }

    printf("\n");
    cout << "Enter the column number of the matrix (from 1 to " << n << ") :" << endl;
    scanf_s("%d", &k);
    k--;


    for (int i = 0; i < n; i++) {
        printf("%lf ", arr[k][i]);
    }
    fclose(ar1);
    FILE* kar;
    err = fopen_s(&kar, "matrix2.txt", "w");
    if (err != 0) {
        perror("to be continued. . .\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        barr[i] = arr[k][i];
    }

    for (int i = 0; i < n; i++) {
        fprintf(kar, "%lf\n", barr[i]);
    }

    fclose(kar);
}