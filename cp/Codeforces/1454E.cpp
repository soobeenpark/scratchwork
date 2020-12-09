#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;


    while (T--) {
        int n; cin >> n;

        // Create adj list
        set<int> adj[n];
        for (int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].insert(b);
            adj[b].insert(a);
        }

        // Init the cnt nodes to all 1
        vector<int> cnt(n, 1);

        // Push all leaf nodes onto queue
        queue<int> leafs;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() == 1) {
                leafs.push(i);
            }
        }

        // Update cnt values while removing all the leaf nodes
        while (!leafs.empty()) {
            // Examine leaf node
            int leaf = leafs.front();
            leafs.pop();
            assert(adj[leaf].size() == 1); // assert is leaf
            int leafParent = *adj[leaf].begin();
            cnt[leafParent] += cnt[leaf];
            cnt[leaf] = 0;

            // Remove leaf node from adj list
            adj[leafParent].erase(leaf);
            adj[leaf].clear();

            // If leafParent is now a leaf itself, add it to the queue
            if (adj[leafParent].size() == 1) {
                leafs.push(leafParent);
            }
        }

        // By now, the only remaining nodes in adj should be the cycle vertices
        long long ans = 0;
        // Apply formula
        for (int i = 0; i < n; i++) {
            if (cnt[i] != 0) {
                ans += (1ll * cnt[i] * (cnt[i] - 1)) / 2;
                ans += 1ll * cnt[i] * (n - cnt[i]);
            }
        }

        cout << ans << endl;
    }
}
