#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_EDGE 50000000
#define MAX_VERT 10000
#define HEAP_FULL(n) (n == MAX_EDGE - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct _EDGE{
    int v1, v2, weight;
} edge;

edge heap[MAX_EDGE];
int parent[MAX_VERT];
int n = 0, num_vet, num_edge;

void insert_min(edge item);
edge delete_min(void);
void wUnion(int i, int j);
int findroot(int i);

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("usage ./hw3 input_filename\n");
        return 0;
    }
    FILE *fp_input;
    FILE *fp_output;
    fp_input = fopen(argv[1], "r");
    if (fp_input == NULL){
        printf("The input file does not exist.\n");
        return 0;
    }
    fp_output = fopen("hw3_result.txt", "w");
    edge temp;
    clock_t init = clock();
    fscanf(fp_input, "%d\n%d\n", &num_vet, &num_edge);
    for (int i = 0; i < num_vet; i++)
        parent[i] = -1;
    for (n = 0; n < num_edge;){
        fscanf(fp_input, "%d %d %d\n", &temp.v1, &temp.v2, &temp.weight);
        insert_min(temp);
    }
    int cost = 0;
    for (int i = 0; i < num_edge - 1; i++){
        temp = delete_min();
        int r1 = findroot(temp.v1);
        int r2 = findroot(temp.v2);
        if (r1 != r2){
            wUnion(r1, r2);
            cost += temp.weight;
            fprintf(fp_output, "%d %d %d\n", temp.v1, temp.v2, temp.weight);
        }
        if (parent[r1] == -1)
            break;
    }

    fprintf(fp_output, "%d\n", cost);
    if(parent[findroot(0)]==-1*num_vet)
        fprintf(fp_output,"CONNECTED\n");
    else
        fprintf(fp_output,"DISCONNECTED\n");

    clock_t end = clock();
    printf("output written to hw3_result.txt.\n");
    printf("running time: %lf seconds\n", (double)(end - init) / CLOCKS_PER_SEC);
    fclose(fp_input);
    fclose(fp_output);
    return 0;
}

void insert_min(edge item)
{
    if (HEAP_FULL(n)){
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }
    int i = ++n;
    while (i > 1 && heap[i / 2].weight > item.weight){
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = item;
}

edge delete_min(){
    if (HEAP_EMPTY(n)){
        fprintf(stderr, "The Heap is empty\n");
        exit(1);
    }
    edge item = heap[1], temp = heap[n--];
    int p = 1, c = 2;
    while (c <= n){
        if ((c < n) && (heap[c].weight > heap[c + 1].weight))
            c++;
        if (temp.weight <= heap[c].weight)
            break;
        heap[p] = heap[c];
        p = c;
        c *= 2;
    }
    heap[p] = temp;
    return item;
}

void wUnion(int i, int j){
    int tmp = parent[i] + parent[j];
    if (parent[i] > parent[j]){
        parent[i] = j;
        parent[j] = tmp;
    }
    else{
        parent[j] = i;
        parent[i] = tmp;
    }
}

int findroot(int i){
    int root, trail, lead;
    for (root = i; parent[root] >= 0; root = parent[root]);
    for (trail = i; trail != root; trail = lead){
        lead = parent[trail];
        parent[trail] = root;
    }
    return root;
} 
/*
int findroot(int i){
    for(;parent[i]>=0;i=parent[i]);
} 
*/
