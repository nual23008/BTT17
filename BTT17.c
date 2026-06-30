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

void Prim() {
    int parent[MAX]; 
    int key[MAX];    
    int da_duyet[MAX];
    int i, j, count, min, u;

    for (i = 0; i < n; i++) {
        key[i] = VO_CUC;
        da_duyet[i] = 0;
    }

    key[0] = 0; 
    parent[0] = -1; 

    for (count = 0; count < n - 1; count++) {
        min = VO_CUC;
        for (i = 0; i < n; i++) {
            if (da_duyet[i] == 0 && key[i] < min) {
                min = key[i];
                u = i;
            }
        }

        da_duyet[u] = 1;

        for (j = 0; j < n; j++) {
            if (ma_tran_ke[u][j] != 0 && da_duyet[j] == 0 && ma_tran_ke[u][j] < key[j]) {
                parent[j] = u;
                key[j] = ma_tran_ke[u][j];
            }
        }
    }

    printf("\n--- CAY KHUNG PRIM ---\n");
    printf("Canh\t\tTrong so\n");
    int tong_chi_phi = 0;
    for (i = 1; i < n; i++) {
        printf("%d - %d\t\t%d\n", parent[i], i, ma_tran_ke[i][parent[i]]);
        tong_chi_phi += ma_tran_ke[i][parent[i]];
    }
    printf("Tong chi phi lam duong: %d\n", tong_chi_phi);
}

struct Canh {
    int u, v, trong_so;
};

int tim_goc(int parent[], int i) {
    while (parent[i] != i) {
        i = parent[i];
    }
    return i;
}

void gop(int parent[], int i, int j) {
    int goc_i = tim_goc(parent, i);
    int goc_j = tim_goc(parent, j);
    parent[goc_i] = goc_j;
}

void Kruskal() {
    struct Canh danh_sach_canh[MAX * MAX];
    int so_canh = 0;
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (ma_tran_ke[i][j] != 0) {
                danh_sach_canh[so_canh].u = i;
                danh_sach_canh[so_canh].v = j;
                danh_sach_canh[so_canh].trong_so = ma_tran_ke[i][j];
                so_canh++;
            }
        }
    }

    for (i = 0; i < so_canh - 1; i++) {
        for (j = 0; j < so_canh - i - 1; j++) {
            if (danh_sach_canh[j].trong_so > danh_sach_canh[j + 1].trong_so) {
                struct Canh tam = danh_sach_canh[j];
                danh_sach_canh[j] = danh_sach_canh[j + 1];
                danh_sach_canh[j + 1] = tam;
            }
        }
    }

    int parent[MAX];
    for (i = 0; i < n; i++) {
        parent[i] = i; 
    }

    printf("\n--- CAY KHUNG KRUSKAL ---\n");
    printf("Canh\t\tTrong so\n");
    int canh_da_chon = 0;
    int tong_chi_phi = 0;

    for (i = 0; i < so_canh; i++) {
        if (canh_da_chon == n - 1) break; 

        int u = danh_sach_canh[i].u;
        int v = danh_sach_canh[i].v;
        int ts = danh_sach_canh[i].trong_so;

        int goc_u = tim_goc(parent, u);
        int goc_v = tim_goc(parent, v);

        if (goc_u != goc_v) {
            printf("%d - %d\t\t%d\n", u, v, ts);
            tong_chi_phi += ts;
            gop(parent, goc_u, goc_v);
            canh_da_chon++;
        }
    }
    printf("Tong chi phi lam duong: %d\n", tong_chi_phi);
}

