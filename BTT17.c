#include <stdio.h>

#define MAX 50
#define VO_CUC 999999 

int n; 
int ma_tran_ke[MAX][MAX];

void Dijkstra(int diem_bat_dau) {
    int khoang_cach[MAX];
    int da_duyet[MAX];
    int i, j, count, min, u;

    for (i = 0; i < n; i++) {
        khoang_cach[i] = VO_CUC;
        da_duyet[i] = 0; 
    }
    
    khoang_cach[diem_bat_dau] = 0; 

    for (count = 0; count < n - 1; count++) {
        min = VO_CUC;
        u = -1;
        for (i = 0; i < n; i++) {
            if (da_duyet[i] == 0 && khoang_cach[i] <= min) {
                min = khoang_cach[i];
                u = i;
            }
        }

        da_duyet[u] = 1; 


        for (j = 0; j < n; j++) {
            if (da_duyet[j] == 0 && ma_tran_ke[u][j] != 0 && khoang_cach[u] != VO_CUC) {
                if (khoang_cach[u] + ma_tran_ke[u][j] < khoang_cach[j]) {
                    khoang_cach[j] = khoang_cach[u] + ma_tran_ke[u][j];
                }
            }
        }
    }

    printf("\n--- KET QUA DIJKSTRA (Tu nga tu %d) ---\n", diem_bat_dau);
    printf("Nga tu\tKhoang cach ngan nhat\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\n", i, khoang_cach[i]);
    }
}

