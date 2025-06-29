#include "wct.h"
#include <stdio.h>
#include <stdlib.h>

void ALOHA(const int N, const double LAMBDA, const double DELAY_LAMBDA) {
    // メモリ確保 (new の代わり)
    Broadcaster* broadcaster = (Broadcaster*)malloc(N * sizeof(Broadcaster));
    if (broadcaster == NULL) {
        printf("Memory allocation failed for ALOHA.\n");
        return;
    }

    int success = 0;
    long long delay = 0; // delayは大きくなる可能性があるのでlong longに

    // 初期化
    for (int index = 0; index < N; index++) {
        Broadcaster_init(&broadcaster[index]);
        Broadcaster_setInterval(&broadcaster[index], LAMBDA);
    }

    for (int slot = 1; slot < SLOT_NUM; slot++) {
        int fired = 0;    // このスロットで送信した数
        int firstFiredBroadcaster = -1; // 最初に送った局
        int firstFiredBroadcasterDelay = 0; // 最初に送った局の遅延時間

        for (int index = 0; index < N; index++) {
            Broadcaster_advancingTime(&broadcaster[index]);

            if (Broadcaster_isFiring(&broadcaster[index])) {
                fired++;
                if (fired == 1) {
                    firstFiredBroadcaster = index;
                    firstFiredBroadcasterDelay = broadcaster[index].delay;
                    Broadcaster_setInterval(&broadcaster[index], LAMBDA);
                } else { // 衝突発生 (fired >= 2)
                    // 衝突発生時は初めに発火したやつと今発火したやつを遅延再送
                    if (fired == 2) {
                        Broadcaster_setDelayInterval(&broadcaster[firstFiredBroadcaster], DELAY_LAMBDA);
                    }
                    Broadcaster_setDelayInterval(&broadcaster[index], DELAY_LAMBDA);
                }
            }
        }

        if (fired == 1) {
            // 衝突してないのでOK
            success++;
            delay += firstFiredBroadcasterDelay;
        }
    }

    printf("%lf, %lf, %lld\n", LAMBDA, (double)success / SLOT_NUM, delay);
    
    // メモリ解放 (delete[] の代わり)
    free(broadcaster);
}