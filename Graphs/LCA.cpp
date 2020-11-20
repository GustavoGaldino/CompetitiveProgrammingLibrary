class LCA{
    public:
        int n;
        vector<int> firstVisit;
        vector<int> secondVisit;
        vector<vector<int>> G;
        vector<vector<int>> up;
        int l;
        vector<bool> vis;
        LCA(vector<vector<int>> &G, int root = 0){
            this->n = G.size();
            this->G = G;
            firstVisit.resize(n);
            secondVisit.resize(n);
            vis.resize(n, false);
            this->l = ceil(log2(n));
            up.resize(l+1, vector<int>(n));
            buildVisit(root);
        }

        void buildVisit(int root){
            vis[root] = true;
            int timer = 0;
            dfs(root, timer, root);
        }

        void dfs(int current, int &timer, int parent){
            firstVisit[current] = timer;
            up[0][current] = parent;
            for(int i = 1 ; i <= l ; i++){
                up[i][current] = up[i-1][up[i-1][current]];
            }
            for(int neighbour : G[current]){
                if(vis[neighbour])
                    continue;
                timer++;
                vis[neighbour] = true;
                dfs(neighbour, timer, current);
           }
           timer++;
           secondVisit[current] = timer;
        }

        // get lca =)
        int get(int u, int v){
            if(isAncestor(u,v))
                return u;
            if(isAncestor(v,u))
                return v;
            for(int i = l ; i >= 0 ; i--){
                if(!isAncestor(up[i][u], v))
                    u = up[i][u];
            }
            /* u now is the highest parent on the tree such that isAncestor(u,v) is false
               so we must return up[0][u] ( his immediatly above parent ) */
            return up[0][u];
        }
        // tells if U is ancestor of V
        bool isAncestor(int u, int v){
            return (firstVisit[v] >= firstVisit[u] && firstVisit[v] <= secondVisit[u]);
        }

        bool isLeaf(int u){
            return (firstVisit[u] + 1 == secondVisit[u]);
        }
};