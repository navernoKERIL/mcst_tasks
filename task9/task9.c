#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr = NULL;
    int n = 0, x = 0;

    while (scanf("%d", &x) == 1){
        arr = realloc(arr, (n+1)*sizeof(int));
        arr[n] = x;
        n++;
    }

    if (n == 0)
        return 0;
    // Ищем лучшую последовательность
    int best_start = 0, cur_start = 0;
    int best_len = 1, cur_len = 1;
    int best_sum = arr[0], cur_sum = arr[0];

    for (int i = 1; i < n; i++){
        if (arr[i] > arr[i-1]){
            cur_len++;
            cur_sum += arr[i];
        }
        else{
            cur_start = i;
            cur_len = 1;
            cur_sum = arr[i];
        }
        // Сравниваем последовательность с лучшей
        if ((cur_len > best_len) || 
            (cur_len == best_len && cur_sum > best_sum)){
                best_start = cur_start;
                best_len = cur_len;
                best_sum = cur_sum;
        }
    }
    for (int i = 0; i < best_len; i++){
        printf("%d ", arr[best_start+i]);
    }
    printf("\n");
    return 0;
}