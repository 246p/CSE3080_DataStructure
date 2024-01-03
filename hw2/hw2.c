#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_HEAP 1000001
#define HEAP_FULL(n) (n == MAX_HEAP - 1)
#define HEAP_EMPTY(n) (!n)
int max[MAX_HEAP];  // max heap
int min[MAX_HEAP];  // min heap
int heap[MAX_HEAP]; // 출력을 할때 필요한 heap
int n = 0;          // 입력된 데이터의 수
void insert_min(int item);
void insert_max(int item);
int delete_min();
int delete_max();

int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("usage ./hw2 input_filename\n");
        return 0;
    }
    FILE *fp_input;
    FILE *fp_output;
    fp_input = fopen(argv[1], "r");
    if (fp_input == NULL){
        printf("The input file does not exist.\n");
        return 0;
    }
    fp_output = fopen("hw2_result.txt", "w");
    char command[10];
    int temp;
    clock_t init = clock();
    while (fscanf(fp_input, "%s", command) != EOF){ // read input file
        switch (command[0]){
        case 'I': // INSERT
            fscanf(fp_input, "%d", &temp);
            insert_max(temp);
            n--;
            insert_min(temp);
            break;
        case 'A': // ASCEND
            temp = n;
            for (int i = 0; i <= temp; i++)
                heap[i] = min[i];
            for (int i = 0; i < temp; i++)
                fprintf(fp_output, "%d ", delete_min());
            fprintf(fp_output, "\n");
            n = temp;
            break;
        case 'D': // DECEND
            temp = n;
            for (int i = 0; i <= temp; i++)
                heap[i] = max[i];
            for (int i = 0; i < temp; i++)
                fprintf(fp_output, "%d ", delete_max());
            fprintf(fp_output, "\n");
            n = temp;
            break;
        }
    }
    clock_t end = clock();
    printf("output written to hw2_result.txt.\n");
    printf("running time: %lf seconds\n", (double)(end - init) / CLOCKS_PER_SEC);
    fclose(fp_input);
    fclose(fp_output);
    return 0;
}

void insert_min(int item){ 
    if(HEAP_FULL(n)){
        fprintf(stderr,"The heap is full.\n");
        exit(1);
    }
    int i =++n;
    while (i > 1 && min[i / 2] > item){
        min[i] = min[i / 2];
        i /= 2;
    }
    min[i] = item;
}
void insert_max(int item){
    if(HEAP_FULL(n)){
        fprintf(stderr,"The heap is full.\n");
        exit(1);
    }
    int i = ++n;
    while ((i != 1) && (max[i / 2] < item)){
        max[i] = max[i / 2];
        i /= 2;
    }
    max[i] = item;
}
int delete_min(){
    if (HEAP_EMPTY(n)){
        fprintf(stderr, "The Heap is empty\n");
        exit(1);
    }
    int item,temp,p,c;
    item = heap[1];
    temp = heap[n--];
    p = 1;
    c = 2;
    while (c <= n){
        if ((c < n) && (heap[c] > heap[c + 1]))
            c++;
        if (temp <= heap[c])
            break;
        heap[p] = heap[c];
        p = c;
        c *= 2;
    }
    heap[p] = temp;
    return item;
}

int delete_max(){
    if (HEAP_EMPTY(n)){
        fprintf(stderr, "The Heap is empty\n");
        exit(1);
    }
    int item,temp,p,c;
    item = heap[1];
    temp = heap[n--];
    p = 1;
    c = 2;
    while (c <= n){
        if ((c < n) && (heap[c] < heap[c + 1]))
            c++;
        if (temp >= heap[c])
            break;
        heap[p] = heap[c];
        p = c;
        c *= 2;
    }
    heap[p] = temp;
    return item;
}