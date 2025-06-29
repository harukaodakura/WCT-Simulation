#include "wct.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // 乱数シードのため

int main(int argc, char *argv[]) {
    int mode;
    int N;
    double DELAY_LAMBDA;

    // 乱数のシードを設定
    srand(time(NULL));

    if (argc < 2) {
        printf("Simulation mode\n");
        printf("  Slotted ALOHA (Normal resend rate): 1\n");
        printf("  Slotted ALOHA (Fixed resend rate): 2\n");
        printf("  TDMA: 3\n");
        printf("Mode: ");
        scanf("%d", &mode);
    } else {
        mode = atoi(argv[1]);
    }

    if (argc < 3) {
        printf("Input number of stations: ");
        scanf("%d", &N);
    } else {
        N = atoi(argv[2]);
    }

    printf("Lambda, Throughput, Delay\n");

    switch (mode) {
    case 1:
        for (double i = 0.0005; i <= 0.03; i += 0.0005) {
            ALOHA(N, i, i);
        }
        break;
    case 2:
        if (argc < 4) {
            printf("Input delay lambda: ");
            scanf("%lf", &DELAY_LAMBDA);
        } else {
            // argv[3]は文字列なのでdoubleに変換する必要がある
            DELAY_LAMBDA = atof(argv[3]);
        }
        
        for (double i = 0.0005; i <= 0.03; i += 0.0005) {
            ALOHA(N, i, DELAY_LAMBDA);
        }
        break;
    case 3:
        for (double i = 0.0005; i <= 0.03; i += 0.0005) {
            TDMA(N, i);
        }
        break;
    }

    return 0;
}