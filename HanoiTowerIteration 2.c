// HanoiTowerLoop.c ? 순수 반복문(C90 호환, 재귀 결과와 동일)
#include <stdio.h>

#define MAXN 30

/* 해당 기둥의 최상단(번호가 가장 작은) 원반 번호를 반환.
   없으면 n+1을 반환해서 "비어있음"을 큰 값으로 표시 */
static int top_disk_on_peg(int n, const int pos[], int peg_idx) {
    int d;
    for (d = 1; d <= n; ++d) {
        if (pos[d] == peg_idx) return d;
    }
    return n + 1;
}

/* 재귀 시그니처를 유지: from, by, to 문자 그대로 사용 */
void HanoiTowerMove_iter(int num, char from, char by, char to) {
    char pegs[3];
    int pos[MAXN + 1];
    unsigned long long total, mv;
    int d;
    int dir_small; /* 가장 작은 원반 회전 방향 (+1 또는 -1) */

    if (num < 1 || num > MAXN) {
        printf("유효한 원판 수는 1~%d\n", MAXN);
        return;
    }

    pegs[0] = from; /* source */
    pegs[1] = by;   /* auxiliary */
    pegs[2] = to;   /* destination */

    /* 시작: 모든 원반은 pegs[0]에 */
    for (d = 1; d <= num; ++d) pos[d] = 0;

    /* 총 이동 횟수 */
    total = (1ULL << num) - 1ULL;

    /* 핵심 수정: 방향 규칙
       - 홀수: S->D->A->S = 인덱스 0->2->1 ( -1 회전 )
       - 짝수: S->A->D->S = 인덱스 0->1->2 ( +1 회전 ) */
    dir_small = (num % 2 == 1) ? -1 : +1;

    for (mv = 1; mv <= total; ++mv) {
        if (mv & 1ULL) {
            /* 홀수 번째 이동: 가장 작은 원반(1번)만 이동 */
            int from_idx = pos[1];
            int to_idx = (from_idx + dir_small + 3) % 3;
            printf("원반1을 %c에서 %c로 이동 \n", pegs[from_idx], pegs[to_idx]);
            pos[1] = to_idx;
        } else {
            /* 짝수 번째 이동: 작은 원반이 없는 두 기둥 사이의 유일한 합법 이동 */
            int peg_small = pos[1];
            int p1 = (peg_small + 1) % 3; /* 나머지 두 기둥 */
            int p2 = (peg_small + 2) % 3;

            int d1 = top_disk_on_peg(num, pos, p1);
            int d2 = top_disk_on_peg(num, pos, p2);

            if (d1 < d2) {
                /* p1의 더 얇은 원반을 p2로 */
                printf("원반%d을(를) %c에서 %c로 이동 \n", d1, pegs[p1], pegs[p2]);
                pos[d1] = p2;
            } else {
                /* p2의 더 얇은 원반을 p1로 */
                printf("원반%d을(를) %c에서 %c로 이동 \n", d2, pegs[p2], pegs[p1]);
                pos[d2] = p1;
            }
        }
    }
}

int main(void) {
    /* 원하면 scanf로 입력 받아도 됨 */
    HanoiTowerMove_iter(5, 'A', 'B', 'C');
    return 0;
}

