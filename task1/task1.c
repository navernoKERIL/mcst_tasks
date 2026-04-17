#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Структура для передачи данных в поток
typedef struct 
{
    int *array;   // указатель на начало блока
    int size;     // размер блока
} ThreadData;

int compare(const void *a, const void *b) 
{
    return *(int*)a - *(int*)b;
}

// Функция потока: сортирует свой блок
void* sort_block(void *arg) 
{
    ThreadData *data = (ThreadData*)arg;
    qsort(data->array, data->size, sizeof(int), compare);
    return NULL;
}

// Сливает два отсортированных блока в один
void merge_two(int *source, int *dest,
               int start_a, int end_a,
               int start_b, int end_b,
               int output_start) 
{
    int idx_a = start_a;
    int idx_b = start_b;
    int idx_out = output_start;
    
    while (idx_a < end_a && idx_b < end_b){
        if (source[idx_a] <= source[idx_b]){
            dest[idx_out++] = source[idx_a++];
        }else{
            dest[idx_out++] = source[idx_b++];
        }
    }
    
    while (idx_a < end_a) 
        dest[idx_out++] = source[idx_a++];

    while (idx_b < end_b) 
        dest[idx_out++] = source[idx_b++];
}

// Сливает все блоки в один отсортированный массив
void merge_all(int *array, int size, int *boundaries, int num_blocks) 
{
    int *buffer = malloc(size * sizeof(int));
    int *source = array;
    int *destination = buffer;
    int blocks = num_blocks;
    
    while (blocks > 1){
        int new_blocks = 0;
        int *new_boundaries = malloc((blocks / 2 + 2) * sizeof(int));
        new_boundaries[0] = 0;
        
        for (int i = 0; i < blocks; i += 2){
            if (i + 1 < blocks){  // Сливаем пару блоков
                int start1 = boundaries[i];
                int end1 = boundaries[i + 1];
                int start2 = boundaries[i + 1];
                int end2 = boundaries[i + 2];
                
                merge_two(source, destination,
                         start1, end1,
                         start2, end2,
                         start1);
                
                new_boundaries[++new_blocks] = end2;
            }else{  // Оставшийся блок копируем
                int start = boundaries[i];
                int end = boundaries[i + 1];
                for (int j = start; j < end; j++) 
                    destination[j] = source[j];
                
                new_boundaries[++new_blocks] = end;
            }
        }
        // Меняем местами source и destination
        int *tmp = source;
        source = destination;
        destination = tmp;
        
        blocks = new_blocks;
        for (int i = 0; i <= blocks; i++) 
            boundaries[i] = new_boundaries[i];
        
        free(new_boundaries);
    }
    
    // Если результат в буфере, копируем обратно
    if (source != array) {
        for (int i = 0; i < size; i++) 
            array[i] = source[i];
    }
    
    free(buffer);
}

int main(int argc, char *argv[]) 
{
    if (argc != 2){
        fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }
    
    int num_threads = atoi(argv[1]);
    if (num_threads <= 0){
        fprintf(stderr, "Error: num_threads must be positive\n");
        return 1;
    }
    
    int *array = NULL;
    int size = 0;
    int value;
    
    while (scanf("%d", &value) == 1){
        array = realloc(array, (size + 1) * sizeof(int));
        array[size++] = value;
    }
    
    if (size == 0) 
        return 0;
    
    // Разбиваем на блоки
    int block_size = size / num_threads;
    int remainder = size % num_threads;
    
    // Создаём потоки
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    ThreadData *thread_data = malloc(num_threads * sizeof(ThreadData));
    
    int offset = 0;
    for (int i = 0; i < num_threads; i++){
        int current_size = block_size + (i < remainder ? 1 : 0);

        thread_data[i].array = array + offset;
        thread_data[i].size = current_size;

        pthread_create(&threads[i], NULL, sort_block, &thread_data[i]);
        offset += current_size;
    }
    
    // Ждём завершения всех потоков
    for (int i = 0; i < num_threads; i++) 
        pthread_join(threads[i], NULL);
    
    // Сохраняем границы блоков
    int *boundaries = malloc((num_threads + 1) * sizeof(int));
    boundaries[0] = 0;
    offset = 0;
    for (int i = 0; i < num_threads; i++){
        int current_size = block_size + (i < remainder ? 1 : 0);
        offset += current_size;
        boundaries[i + 1] = offset;
    }
    
    // Сливаем блоки
    merge_all(array, size, boundaries, num_threads);
    
    // Выводим результат
    for (int i = 0; i < size; i++){
        printf("%d", array[i]);
        if (i < size - 1)
            printf(" ");
    }
    printf("\n");
    
    // Освобождаем память
    free(boundaries);
    free(threads);
    free(thread_data);
    free(array);
    
    return 0;
}