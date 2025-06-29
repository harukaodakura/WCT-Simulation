#include "wct.h"
#include <stdio.h>
#include <stdlib.h>

void TDMA(const int N, const double LAMBDA) {
    // メモリ確保
    Broadcaster* broadcaster = (Broadcaster*)malloc(N * sizeof(Broadcaster));
    if (broadcaster == NULL) {
        printf("Memory allocation failed for TDMA.\n");
        return;
    }
    
    int success = 0;
    long long delay = 0;

    // 初期化
    for (int index = 0; index < N; index++) {
        Broadcaster_init(&broadcaster[index]);
        Broadcaster_setInterval(&broadcaster[index], LAMBDA);
    }

    for (int slot = 1; slot < SLOT_NUM; slot++) {
        for (int index = 0; index < N; index++) {
            Broadcaster_advancingTime(&broadcaster[index]);

            if (Broadcaster_isFiring(&broadcaster[index])) {
                // 自分のスロットでなければ遅延状態にする
                if (slot % N != index) {
                    broadcaster[index].isDelaying = true;
                } else {
                    // 自分のスロットなので成功 (衝突は起こりえない)
                    success++;
                    delay += broadcaster[index].delay;
                    Broadcaster_setInterval(&broadcaster[index], LAMBDA); // 遅延状態でなくなる
                }
            }
        }
    }

    printf("%lf, %lf, %lld\n", LAMBDA, (double)success / SLOT_NUM, delay);
    
    // メモリ解放
    free(broadcaster);
}