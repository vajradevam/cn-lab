#include <stdio.h>

void sort(int arr[]) {
    int n = arr[0];
    for (int i = 1; i < n + 1; i++) {
        for (int j = i; j < n-i-1 + 1; j++) {
            if (arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sort2(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sort3(int arr[]) {

    int n = arr[0];

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n; j++) {

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {

    int arr[5] = {4, 55, 234, 79, 110};

    sort3(arr);

    for (int i = 1; i < 5; i++) {
            printf("%d ", arr[i]);
    }

        printf("\n");

}