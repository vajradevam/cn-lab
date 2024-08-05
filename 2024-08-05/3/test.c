#include <stdio.h>

void sort(int arr[]) {
    int n = arr[0];
    for (int i = 1; i < n + 1; i++) {
        for (int j = i; j < n-i-1 + 1; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {

    int arr[4] = {3, 55, 33, 79};

    sort(arr);

    for (int i = 1; i < arr[0] + 1; i++) {
            printf("%d ", arr[i]);
    }

        printf("\n");

}