#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

typedef long long ll;

int n;
ll F[81];
ll prefixF[81];
ll alpha, beta, gamma_val;

// Memoization tables
ll dp1[81][81];
ll dp2_L[81][81], dp2_R[81][81];
ll dp3[81][81][82][2];

// Helper to get sum of frequencies in O(1)
ll get_sumF(int i, int j) {
    if (i > j) return 0;
    return prefixF[j] - prefixF[i - 1];
}

// --- Part 1 Solver ---
ll solve_p1(int i, int j) {
    if (i > j) return 0;
    if (dp1[i][j] != -1) return dp1[i][j];

    ll min_cost = -1;
    ll current_sumF = get_sumF(i, j);

    for (int k = i; k <= j; ++k) {
        ll cost = solve_p1(i, k - 1) + solve_p1(k + 1, j);
        if (min_cost == -1 || cost < min_cost) {
            min_cost = cost;
        }
    }
    return dp1[i][j] = min_cost + current_sumF;
}

// --- Part 2 Solvers ---
ll solve_p2_R(int i, int j); // Forward declaration

ll solve_p2_L(int i, int j) {
    if (i > j) return 0;
    if (dp2_L[i][j] != -1) return dp2_L[i][j];

    ll min_cost = -1;
    ll current_sumF = get_sumF(i, j);
    int parent_pos = i - 1;

    for (int k = i; k <= j; ++k) {
        ll cost = (ll)(k - parent_pos) * current_sumF + solve_p2_R(i, k - 1) + solve_p2_L(k + 1, j);
        if (min_cost == -1 || cost < min_cost) {
            min_cost = cost;
        }
    }
    return dp2_L[i][j] = min_cost;
}

ll solve_p2_R(int i, int j) {
    if (i > j) return 0;
    if (dp2_R[i][j] != -1) return dp2_R[i][j];

    ll min_cost = -1;
    ll current_sumF = get_sumF(i, j);
    int parent_pos = j + 1;

    for (int k = i; k <= j; ++k) {
        ll cost = (ll)(parent_pos - k) * current_sumF + solve_p2_R(i, k - 1) + solve_p2_L(k + 1, j);
        if (min_cost == -1 || cost < min_cost) {
            min_cost = cost;
        }
    }
    return dp2_R[i][j] = min_cost;
}

// --- Part 3 Solver ---
ll solve_p3(int i, int j, int p, int dir) {
    if (i > j) return 0;
    if (dp3[i][j][p + 1][dir] != -1) return dp3[i][j][p + 1][dir];

    ll min_cost = -1;
    ll current_sumF = get_sumF(i, j);

    for (int k = i; k <= j; ++k) {
        int move_dir = (k > p) ? 0 : 1; // 0 for L->R, 1 for R->L
        ll reversal_penalty = (p != 0 && dir != move_dir) ? gamma_val : 0;

        ll cost_this_level = current_sumF * (alpha * abs(k - p) + beta + reversal_penalty);
        ll cost_subtrees = solve_p3(i, k - 1, k, move_dir) + solve_p3(k + 1, j, k, move_dir);
        ll total_k_cost = cost_this_level + cost_subtrees;

        if (min_cost == -1 || total_k_cost < min_cost) {
            min_cost = total_k_cost;
        }
    }
    return dp3[i][j][p + 1][dir] = min_cost;
}


void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp1[i][j] = -1;
            dp2_L[i][j] = -1;
            dp2_R[i][j] = -1;
            for (int p = 0; p <= n + 1; ++p) {
                dp3[i][j][p][0] = -1;
                dp3[i][j][p][1] = -1;
            }
        }
    }
    prefixF[0] = 0;
    for (int i = 1; i <= n; ++i) {
        prefixF[i] = prefixF[i - 1] + F[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int type;
    cin >> type;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> F[i];
    }

    init();

    if (type == 1) {
        cout << solve_p1(1, n) << endl;
    } else if (type == 2) {
        ll min_total_cost = -1;
        ll current_sumF = get_sumF(1, n);
        for (int k = 1; k <= n; ++k) {
            ll cost = (ll)k * current_sumF + solve_p2_R(1, k - 1) + solve_p2_L(k + 1, n);
            if (min_total_cost == -1 || cost < min_total_cost) {
                min_total_cost = cost;
            }
        }
        cout << min_total_cost << endl;
    } else if (type == 3) {
        cin >> alpha >> beta >> gamma_val;
        ll fixed_return_cost = 0;
        for (int i = 1; i <= n; ++i) {
            fixed_return_cost += F[i] * alpha * i;
        }
        // Initial call: parent p=0, dir=0 (convention for L->R)
        ll search_cost = solve_p3(1, n, 0, 0);
        cout << search_cost + fixed_return_cost << endl;
    }

    return 0;
}