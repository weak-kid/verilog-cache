#include <bits/stdc++.h>

using namespace std;
#define M 64
#define N 60
#define K 32

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tkts = 0;
    int cache_hit = 0;
    int quers = 0;
    vector<vector<int>> CACHE1(32, vector<int>(2, -1)); // хранит tag и dirty, размер - количество кеш линий / 2
    vector<vector<int>> CACHE2(32, vector<int>(2, -1)); // хранит tag и dirty, размер - количество кеш линий / 2
    vector<int> old1(32); //  размер - количество кеш линий / 2
    vector<int> old2(32); //  размер - количество кеш линий / 2
    int f = 0;
    tkts += 1;
    int s = M * K + N * K * 2;
    tkts += 1;
    int time = 1;
    for (int i = 0; i < M; i++) {
        tkts += 2;
        for (int j = 0; j < N; j++) {
            tkts += 3;
            int t = M * K;
            for (int k = 0; k < K; k++) {
                tkts += 2;
                int set = ((f + k) >> 4) % 32; // set вычисляем так, берем индекс в памяти, сдвигаем на offset, и берем только принажлежащие сету
                tkts += 1;
                int tag = (f + k) >> 9; // уберем из индекса set и offset
                tkts += 1;
                if (CACHE1[set][0] == tag) { // попадание
                    tkts += 6; // отклик кеша при попадании
                    cache_hit++;
                    quers++;
                    old1[set] = time++;
                } else if (CACHE2[set][0] == tag) { // попадание
                    tkts += 6; // отклик кеша при попадании
                    cache_hit++;
                    quers++;
                    old2[set] = time++;
                } else { // промах
                    tkts += 4; // отклик кеша при промахе
                    tkts += 100; // отклик памяти
                    quers++;
                    if (old1[set] > old2[set]) {
                        if (CACHE2[set][1] == 1) { // если линия была изменена, нужно записать изменения в память, не влияет на попадания
                            tkts += 100; // отклик памяти
                            CACHE2[set][1] = 0;
                        }
                        CACHE2[set][0] = tag;
                        old2[set] = time++;
                    } else {
                        if (CACHE1[set][1] == 1) {
                            tkts += 100; // отклик памяти
                            CACHE1[set][1] = 0;
                        }
                        CACHE1[set][0] = tag;
                        old1[set] = time++;
                    }
                }
                set = ((t + j * 2) >> 4) % 32;
                tag = (t + j * 2) >> 9;
                if (CACHE1[set][0] == tag) {
                    tkts += 6; // отклик кеша при попадании
                    cache_hit++;
                    quers++;
                    old1[set] = time++;
                } else if (CACHE2[set][0] == tag) {
                    tkts += 6; // отклик кеша при попадании
                    cache_hit++;
                    quers++;
                    old2[set] = time++;
                }else{
                    quers++;
                    tkts += 4; // отклик кеша при промахе
                    tkts += 100; // отклик памяти
                    if (old1[set] > old2[set]) {
                        if (CACHE2[set][1] == 1) {
                            tkts += 100; // отклик памяти
                            CACHE2[set][1] = 0;
                        }
                        CACHE2[set][0] = tag;
                        old2[set] = time++;
                    } else {
                        if (CACHE1[set][1] == 1) {
                            tkts += 100; // отклик памяти
                            CACHE1[set][1] = 0;
                        }
                        CACHE1[set][0] = tag;
                        old1[set] = time++;
                    }
                }
                t += N * 2;
                tkts += 1;
            }
            int set = ((s + j * 4) >> 4) % 32;
            int tag = (s + j * 4) >> 9;
            if (CACHE1[set][0] == tag) {
                tkts += 6; // отклик кеша при попадании
                cache_hit++;
                quers++;
                CACHE1[set][1] = 1;
                old1[set] = time++;
            } else if (CACHE2[set][0] == tag) {
                tkts += 6; // отклик кеша при попадании
                cache_hit++;
                quers++;
                CACHE2[set][1] = 1;
                old2[set] = time++;
            } else {
                tkts += 4; // отклик кеша при промахе
                tkts += 100; // отклик памяти
                quers++;
                if (old1[set] > old2[set]) {
                    if (CACHE2[set][1] == 1) {
                        tkts += 100; // отклик памяти
                        CACHE2[set][1] = 0;
                    }
                    CACHE2[set][0] = tag;
                    CACHE2[set][1] = 1;
                    old2[set] = time++;
                } else {
                    if (CACHE1[set][1] == 1) {
                        tkts += 100; // отклик памяти
                        CACHE1[set][1] = 0;
                    }
                    CACHE1[set][0] = tag;
                    CACHE1[set][1] = 1;
                    old1[set] = time++;
                }
            }
        }
        f += K;
        s += N * 4;
        tkts += 2;
    }
    cout << tkts << endl;
    cout << cache_hit << " " << quers << " " << (double )cache_hit / quers << endl;
    int cache_hit_ans = 224175;
    cout << cache_hit_ans << " " << cache_hit_ans << " " << (double )224175 / quers << endl; // ответ полученный при помощи модулирования работы кеша
    return 0;
}

