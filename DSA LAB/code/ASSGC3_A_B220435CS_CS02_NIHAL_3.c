#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct c_Node {
    int v;
    struct c_Node *n;
};

struct c_Graph {
    int v;
    struct c_Node **a;
};

struct c_Graph *c_create_Graph(int v) ;
struct c_Node *create_node(int v);
struct c_Graph *c_Insert(struct c_Graph *g, int p, int v);
struct c_Graph *Create_c_List(struct c_Graph *g, char i[]);
void c_DFS(struct c_Graph *g, int s, int v[]);
int c_Helper(struct c_Graph *g, int c, int p, int v[]) ;
int check_c_Cycle(struct c_Graph *g);
int check_Valid(struct c_Graph *g) ;
void c_all_path(struct c_Graph *g, int c, int e, int v[], int p[], int pi);
void c_find_path(struct c_Graph *g, int start_vertex, int end_vertex) ;


int main() {
    int v;
    scanf("%d", &v);
    scanf("\n");
    struct c_Graph *g = NULL;
    g = c_create_Graph(v);
    int k = v;
    while (k > 0) {
        char i[100];
        fgets(i, 100, stdin);
        g = Create_c_List(g, i);
        k--;
    }
    int visited[v];
    for (int i = 0; i < v; i++) {
        visited[i] = 0;
    }
    char c;
    int x, y;
    while (1) {
        scanf(" %c", &c); 
        if (c == 'a') {
            scanf("%d", &x);
            scanf("%d", &y);
            c_find_path(g, x, y);
        } else if (c == 't') {
            x = check_Valid(g);
            printf("%d \n", x);
        } else if (c == 'x') {
            break;
        }
    }
    return 1;
}

struct c_Graph *c_create_Graph(int v) {
    struct c_Graph *g = (struct c_Graph *)malloc(sizeof(struct c_Graph));
    g->v = v;
    g->a = (struct c_Node **)malloc(sizeof(struct c_Node *) * v);
    for (int i = 0; i < v; i++) {
        g->a[i] = NULL;
    }
    return g;
}

struct c_Node *create_node(int v) {
    struct c_Node *t = (struct c_Node *)malloc(sizeof(struct c_Node));
    t->v = v;
    t->n = NULL;
    return t;
}


struct c_Graph *c_Insert(struct c_Graph *g, int p, int v) {
    struct c_Node *n = g->a[p];
    if (n == NULL) {
        n = create_node(v);
        g->a[p] = n;
    } else {
        while (n->n != NULL) {
            n = n->n;
        }
        n->n = create_node(v);
    }
    return g;
}

struct c_Graph *Create_c_List(struct c_Graph *g, char i[]) {
    int x = 0;
    int p = 0, v = 0;
    while (i[x] != ' ') {
        p = p * 10 + (int)(i[x] - '0');
        x++;
    }
    while (i[x] != '\n' && i[x] == ' ') {
        x++;
        v = 0;
        while (i[x] >= '0' && i[x] <= '9') {
            v = v * 10 + (int)(i[x] - '0');
            x++;
        }
        g = c_Insert(g, p, v);
    }
    return g;
}

void c_DFS(struct c_Graph *g, int s, int v[]) {
    v[s] = 1;
    struct c_Node *n = g->a[s];
    while (n) {
        if (!v[n->v]) {
            c_DFS(g, n->v, v);
        }
        n = n->n;
    }
}

int c_Helper(struct c_Graph *g, int c, int p, int v[]) {
    v[c] = 1;
    struct c_Node *n = g->a[c];
    while (n) {
        if (!v[n->v]) {
            if (c_Helper(g, n->v, c, v)) {
                return 1;
            }
        } else if (n->v != p) {
            return 1;
        }
        n = n->n;
    }
    return 0;
}

int check_c_Cycle(struct c_Graph *g) {
    int *v = (int *)malloc(sizeof(int) * g->v);
    for (int i = 0; i < g->v; i++) {
        v[i] = 0;
    }
    for (int i = 0; i < g->v; i++) {
        if (!v[i]) {
            if (c_Helper(g, i, -1, v)) {
                free(v);
                return 1;
            }
        }
    }
    free(v);
    return 0; 
}

int check_Valid(struct c_Graph *g) {
    int v[g->v];
    for (int i = 0; i < g->v; i++) {
        v[i] = 0;
    }
    int rc = 0;
    for (int i = 0; i < g->v; i++) {
        if (!v[i]) {
            rc++;
            c_DFS(g, i, v);
        }
    }
    if (rc != 1) {
        return -1; 
    }
    for (int i = 0; i < g->v; i++) {
        if (!v[i]) {
            return -1; 
        }
    }
    if (check_c_Cycle(g)) {
        return -1; 
    }
    int ec = 0;
    for (int i = 0; i < g->v; i++) {
        struct c_Node *n = g->a[i];
        while (n) {
            ec++;
            n = n->n;
        }
    }
    if (ec <= g->v - 1) {
        return -1; 
    }
    return 1; 
}

void c_all_path(struct c_Graph *g, int c, int e, int v[], int p[], int pi) {
    v[c] = 1;
    p[pi] = c;
    pi++;

    if (c == e) {
        for (int i = 0; i < pi; i++) {
            printf("%d ", p[i]);
        }
        printf("\n");
    } else {
        struct c_Node *n = g->a[c];
        while (n) {
            if (v[n->v] == 0) {
                c_all_path(g, n->v, e, v, p, pi);
            }
            n = n->n;
        }
    }

    v[c] = 0;
    pi--;
}

void c_find_path(struct c_Graph *g, int start_vertex, int end_vertex) {
    int visited[g->v];
    int path[g->v];
    for (int i = 0; i < g->v; i++) {
        visited[i] = 0;
    }
    c_all_path(g, start_vertex, end_vertex, visited, path, 0);
}

