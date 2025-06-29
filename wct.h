#ifndef WCT_H
#define WCT_H

#include <math.h>
#include <stdbool.h> // bool, true, false を使うため
#include <stdlib.h>  // rand(), RAND_MAX のため

// C++の<random>の代わりにCの標準的な乱数生成器を使う
// 0から1の範囲の実数乱数を生成
static inline double rand_double() {
    return (double)rand() / RAND_MAX;
}

// 共通の定数
#define SLOT_NUM 100000 // スロットの数

// 端末（Broadcaster）の構造体
typedef struct {
    int delay;          // 遅延時間(スロット単位)
    int fireTime;       // 発火までの残り時間(スロット単位)
    bool isDelaying;    // 現在、遅延状態か
} Broadcaster;

// --- Broadcaster構造体を操作する関数群 ---

// 構造体の初期化（C++のコンストラクタの代わり）
static inline void Broadcaster_init(Broadcaster* self) {
    self->delay = 0;
    self->fireTime = 0;
    self->isDelaying = false;
}

// データ発生間隔の計算
static inline double interval(double random_val, double lambda) {
    return ((-1.0 / lambda) * log(random_val)) + 1.0;
}

// 通常時のデータ発生間隔を設定
static inline void Broadcaster_setInterval(Broadcaster* self, double lambda) {
    self->fireTime = (int)interval(rand_double(), lambda);
    self->isDelaying = false;
}

// 遅延時のデータ発生間隔を設定
static inline void Broadcaster_setDelayInterval(Broadcaster* self, double delay_lambda) {
    self->fireTime = (int)interval(rand_double(), delay_lambda);
    self->isDelaying = true;
}

// 送信するかどうか
static inline bool Broadcaster_isFiring(const Broadcaster* self) {
    return self->fireTime == 0;
}

// 時間を進ませる
static inline void Broadcaster_advancingTime(Broadcaster* self) {
    if (self->fireTime >= 1) {
        self->fireTime--;
    }
    // 遅延状態かどうかで遅延時間を変える
    if (self->isDelaying) {
        self->delay++;
    } else {
        self->delay = 0;
    }
}

// --- シミュレーション本体の関数宣言 ---
void ALOHA(int N, double LAMBDA, double DELAY_LAMBDA);
void TDMA(int N, double LAMBDA);

#endif // WCT_H