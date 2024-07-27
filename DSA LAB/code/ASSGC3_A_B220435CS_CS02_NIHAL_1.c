#include <stdio.h>
#include <stdlib.h>


void node_Mark(int adjacent[][100], int c_node, int c_row, int c_visited[]);
void node_Mark_2(int adjacent[][100], int c_node, int c_row, int c_visited[], int *c_compnt);
int num_connected_comp(int adjacent[][100], int c_node);
void comp_size(int adjacent[][100], int c_node);
int num_bridges(int adjacent[][100], int c_node);
int num_articulation_points(int adjacent[][100], int c_node);
int c_Conversion(const char *array, int c_Start, int c_End);



int main() {

    int c_node;
    int adjacent[100][100];
    scanf(" %d", &c_node);
    getchar();

    for (int i = 0; i < c_node; i++) {
        for (int j = 0; j < c_node; j++) {
            adjacent[i][j] = 0;
        }
    }

    for (int i = 0; i < c_node; i++) {
        char array[100];
        scanf(" %[^\n]", array);
        getchar();

        int c_index;
        int j = 0;
        while (array[j] != ' ' && array[j] != '\0') {
            j++;
        }
        c_index = c_Conversion(array, 0, j);
        if (array[j] == ' ') {
            j++;
        }

        while (array[j] != '\0') {
            int k = j;
            while (array[j] != ' ' && array[j] != '\0') {
                j++;
            }
            int v = c_Conversion(array, k, j);
            adjacent[c_index - 1][v - 1] = 1;
            adjacent[v - 1][c_index - 1] = 1;
            if (array[j] == ' ') {
                j++;
            }
        }
    }

    char ch;
    do {
        scanf(" %c", &ch);

        switch (ch) {
            case 'n':
                printf("%d\n", num_connected_comp(adjacent, c_node));
                break;
            case 's':
                comp_size(adjacent, c_node);
                printf("\n");
                break;
            case 'b':
                printf("%d\n", num_bridges(adjacent, c_node));
                break;
            case 'a':
                printf("%d\n", num_articulation_points(adjacent, c_node));
                break;
            case 't':
                exit(0);
                break;
        }
    } while (1);

    return 1;
}


void node_Mark(int adjacent[][100], int c_node, int c_row, int c_visited[]) {
    c_visited[c_row] = 1;
    for (int i = 0; i < c_node; i++) {
        if (adjacent[c_row][i] && !c_visited[i]) {
            node_Mark(adjacent, c_node, i, c_visited);
        }
    }
}

void node_Mark_2(int adjacent[][100], int c_node, int c_row, int c_visited[], int *c_compnt) {
    (*c_compnt)++;
    c_visited[c_row] = 1;
    for (int i = 0; i < c_node; i++) {
        if (adjacent[c_row][i] && !c_visited[i]) {
            node_Mark_2(adjacent, c_node, i, c_visited, c_compnt);
        }
    }
}

int num_connected_comp(int adjacent[][100], int c_node) {
    int c_visited[c_node];
    int c_compnt = 0;

    for (int i = 0; i < c_node; i++) {
        c_visited[i] = 0;
    }
    for (int i = 0; i < c_node; i++) {
        if (!c_visited[i]) {
            node_Mark(adjacent, c_node, i, c_visited);
            c_compnt++;
        }
    }
    return c_compnt;
}

void comp_size(int adjacent[][100], int c_node) {
    int c_visited[c_node];

    for (int i = 0; i < c_node; i++) {
        c_visited[i] = 0;
    }
    for (int i = 0; i < c_node; i++) {
        if (!c_visited[i]) {
            int c_compnt = 0;
            node_Mark_2(adjacent, c_node, i, c_visited, &c_compnt);
            printf("%d ", c_compnt);
        }
    }
}


int num_bridges(int adjacent[][100], int c_node) {
    int num_bridges = 0;
    for (int i = 0; i < c_node; i++) {
        for (int j = 0; j < c_node; j++) {
            if (adjacent[i][j] != 0) {
                adjacent[i][j] = 0;
                adjacent[j][i] = 0;
                int a2 = num_connected_comp(adjacent, c_node);
                adjacent[i][j] = 1;
                adjacent[j][i] = 1;
                int a1 = num_connected_comp(adjacent, c_node);
                if (a1 != a2) {
                    num_bridges++;
                }
            }
        }
    }
    return num_bridges / 2;
}


int num_articulation_points(int adjacent[][100], int c_node) {
    int vertex = 0;
    for (int z = 0; z < c_node; z++) {
        int d[100][100];
        int k = 0;
        int l = 0;
        for (int i = 0; i < c_node; i++) {
            if (i == z) {
                continue;
            }
            for (int j = 0; j < c_node; j++) {
                if (j == z) {
                    continue;
                }
                d[k][l] = adjacent[i][j];
                l++;
            }
            k++;
            l = 0;
        }

        int a1 = num_connected_comp(d, c_node - 1);
        int a2 = num_connected_comp(adjacent, c_node);

        if (a1 != a2) {
            vertex++;
        }
    }
    return vertex;
}



int c_Conversion(const char *array, int c_Start, int c_End) {
    int answer = 0;
    for (int i = c_Start; array[i] != '\0' && i < c_End; i++) {
        answer = answer * 10 + (array[i] - '0');
    }
    return answer;
}
