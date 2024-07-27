#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct c_queue {
    int str[100];
    int f, r;
};

struct c_graph {
    int** adjacent_Graph;
    int vertex_of_num;
};


struct c_queue* create_queue_func();
void c_enqueue_funct(struct c_queue* q, int c_value);
int c_dequeue_funct(struct c_queue* q);
bool check_empty(struct c_queue* q);
struct c_graph* create_graph_funct(int vertex_of_num);
void c_add_edge(struct c_graph* g, int c_Src, int c_Dest);
int sort_funct_topologically(struct c_graph* g);
int comp_Strong_funct(struct c_graph* g);


int main() {
    int vertex_of_num;
    char user_command;
    scanf("%d", &vertex_of_num);
    struct c_graph* g = create_graph_funct(vertex_of_num);

    for (int i = 0; i < vertex_of_num; ++i) {
        for (int j = 0; j < vertex_of_num; ++j) {
            scanf("%d", &g->adjacent_Graph[i][j]);
        }
    }

    while (1) {
        scanf(" %c", &user_command);

        switch (user_command) {
            case 't':
                printf("%d\n", sort_funct_topologically(g));
                break;
            case 'c':
                printf("%d\n", comp_Strong_funct(g));
                break;
            case 'x':
                return 0;
        }
    }

    return 1;
}

struct c_queue* create_queue_func() {
    struct c_queue* q = (struct c_queue*)malloc(sizeof(struct c_queue));
    q->f = -1;
    q->r = -1;
    return q;
}

void c_enqueue_funct(struct c_queue* q, int c_value) {
    if (q->r == 99) {
        return;
    }
    if (q->f == -1) {
        q->f = 0;
    }
    q->r++;
    q->str[q->r] = c_value;
}

int c_dequeue_funct(struct c_queue* q) {
    if (q->f == -1) {
        return -1;
    }
    int c_value = q->str[q->f];
    q->f++;
    if (q->f > q->r) {
        q->f = q->r = -1;
    }
    return c_value;
}

bool check_empty(struct c_queue* q) {
    return q->f == -1;
}

struct c_graph* create_graph_funct(int vertex_of_num) {
    struct c_graph* g = (struct c_graph*)malloc(sizeof(struct c_graph));
    g->vertex_of_num = vertex_of_num;
    g->adjacent_Graph = (int**)malloc(vertex_of_num * sizeof(int*));
    for (int i = 0; i < vertex_of_num; ++i) {
        g->adjacent_Graph[i] = (int*)malloc(vertex_of_num * sizeof(int));
    }
    return g;
}

void c_add_edge(struct c_graph* g, int c_Src, int c_Dest) {
    g->adjacent_Graph[c_Src][c_Dest] = 1;
}

int sort_funct_topologically(struct c_graph* g) {
    int c_ind[100] = {0};

    for (int i = 0; i < g->vertex_of_num; ++i) {
        for (int j = 0; j < g->vertex_of_num; ++j) {
            if (g->adjacent_Graph[i][j] == 1) {
                c_ind[j]++;
            }
        }
    }

    struct c_queue* q = create_queue_func();

    for (int i = 0; i < g->vertex_of_num; ++i) {
        if (c_ind[i] == 0) {
            c_enqueue_funct(q, i);
        }
    }

    int cnt = 0;

    while (!check_empty(q)) {
        int c_Vertex = c_dequeue_funct(q);
        cnt++;

        for (int i = 0; i < g->vertex_of_num; ++i) {
            if (g->adjacent_Graph[c_Vertex][i] == 1) {
                c_ind[i]--;
                if (c_ind[i] == 0) {
                    c_enqueue_funct(q, i);
                }
            }
        }
    }

    if (cnt != g->vertex_of_num) {
        return -1;
    }

    return 1;
}

int comp_Strong_funct(struct c_graph* g) {
    int cnt = 0;

    bool v[100] = {false};

    for (int i = 0; i < g->vertex_of_num; ++i) {
        if (!v[i]) {
            struct c_queue* q = create_queue_func();
            c_enqueue_funct(q, i);
            v[i] = true;
            while (!check_empty(q)) {
                int c_Vertex = c_dequeue_funct(q);
                for (int j = 0; j < g->vertex_of_num; ++j) {
                    if (g->adjacent_Graph[j][c_Vertex] == 1 && !v[j]) {
                        c_enqueue_funct(q, j);
                        v[j] = true;
                    }
                }
            }
            cnt++;
        }
    }

    return cnt;
}
