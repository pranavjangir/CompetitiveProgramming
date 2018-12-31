#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 500000

int N;
int A[MAXN];
long long sum;

#define TOO_SMALL -1
#define OK 0
#define TOO_BIG 1

int is_score(int value) {
    vector<int> C(N+1,0);
    for (int i = 0; i < N; ++i) ++C[A[i]];
    ++C[value];

    int less = 0;
    long long left = 0, right = 0;
    for (int k = 0, i = 0; k <= N; k++) {
        int val = (i == k && (i == N || A[i] < value)) ? value : A[i++];
        left += val;
        --C[val];
        right -= min(val, k);
        less += C[k];
        right += N-k-less;
        if (left > right + (long long)(k+1)*k) {
            return (i == k) ? TOO_BIG : TOO_SMALL;
        }
    }
    return OK;
}

int main(int,char**) {
    ios_base::sync_with_stdio(false);
    
    scanf("%d", &N);
    sum = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", A + i);
        sum += A[i];
    }

    sort(A,A+N,greater<int>());
    int parity = sum & 1;
    int lo = 0, hi = (N - parity) / 2, lores = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (is_score(2*mid + parity) == TOO_SMALL) {
            lo = mid + 1;
        } else {
            lores = mid;
            hi = mid - 1;
        }
    }
    
    lo = lores; 
    hi = (N - parity) / 2; 
    int hires = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (is_score(2*mid + parity) == TOO_BIG) {
            hi = mid - 1;
        } else {
            hires = mid;
            lo = mid + 1;
        }
    }
    
    if (lores == -1 || hires == -1) printf("-1\n"); 
    else {
        for (int i = lores; i <= hires; ++i) printf("%d ", 2*i+parity);
        printf("\n");
    }
}
