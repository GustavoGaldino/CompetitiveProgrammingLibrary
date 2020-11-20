class SegTree{
    public:
        vector<int> v;
        vector<long long> tree;
        int n;
        SegTree(vector<int> v){
            this->n = (int)v.size();
            this->v=v;
            tree.resize(4*n);
            build(0,0,n-1);
        }

        SegTree(int n){
            this->n = n;
            tree.resize(4*n);
        }

        SegTree(){}

        void build(int treeIndex, int l, int r){
            int leftChild = 2*treeIndex+1;
            int rightChild = 2*treeIndex+2;
            int m = (r+l)/2;
            // tree child, the segment we are analyzing only consists of one element in the vector
            if(l == r){
                tree[treeIndex] = (long long)v[l];
            }
            else{
                build(leftChild, l,m);
                build(rightChild,m+1,r);
                tree[treeIndex] = tree[leftChild] + tree[rightChild];
            }
        }

        long long query(int L, int R){
            return recursiveQuery(L,R,0,0,n-1);
        }

        long long recursiveQuery(int L, int R, int treeIndex, int l, int r){
            int leftChild = 2*treeIndex+1;
            int rightChild = 2*treeIndex+2;
            int m = (r+l)/2;
            // totally inside the interval
            if(l >= L && r <= R){
                return tree[treeIndex];
            }
            // not inside the interval at all
            else if((r < L) || (l > R)){
                return (long long)0;
            }
            // partially inside the interval
            else{
                return (recursiveQuery(L,R,leftChild,l,m) + recursiveQuery(L,R,rightChild,m+1,r) );
            }
        }

        // assign v[i] = x;
        void updateTo(int i, int x){
            recursiveUpdateTo(i,x,0,0,n-1);
        }

        void recursiveUpdateTo(int i, int x, int treeIndex, int l, int r){
            int leftChild = 2*treeIndex+1;
            int rightChild = 2*treeIndex+2;
            int m = (r+l)/2;
            if(!(i >= l && i <= r)){
                return;
            }
            if(l == r){
                tree[treeIndex] = (long long)x;
            }
            else{
                recursiveUpdateTo(i,x,leftChild,l,m);
                recursiveUpdateTo(i,x,rightChild,m+1,r);
                tree[treeIndex] = tree[leftChild] + tree[rightChild];
            }
        }

        // assign v[i] = v[i] + x;
        void updateAdd(int i, int x){
            recursiveUpdateAdd(i,x,0,0,n-1);
        }

        void recursiveUpdateAdd(int i, int x, int treeIndex, int l, int r){
            int leftChild = 2*treeIndex+1;
            int rightChild = 2*treeIndex+2;
            int m = (r+l)/2;
            if(!(i >= l && i <= r)){
                return;
            }
            if(l == r){
                tree[treeIndex] =  tree[treeIndex] + (long long)x;
            }
            else{
                recursiveUpdateAdd(i,x,leftChild,l,m);
                recursiveUpdateAdd(i,x,rightChild,m+1,r);
                tree[treeIndex] = tree[leftChild] + tree[rightChild];
            }
        }
};

class HLD{
    public:
        int n;
        vector<vector<int>> G;
        vector<int> sz;
        vector<int> pos;
        vector<int> headOfChain;
        vector<int> v;
        vector<int> val;
        vector<int> parents;
        SegTree Seg;
        int timer;
        HLD(vector<vector<int>> &G, vector<int> val,int root = 0){
            this->n = G.size();
            this->val = val;
            sz.resize(n,1);
            pos.resize(n);
            headOfChain.resize(n);
            parents.resize(n);
            v.resize(n);
            this->timer = 0;
            this->G = G;
            dfs(root);
            headOfChain[root] = root;
            buildHLD(root);
            Seg = *(new SegTree(v));
        }

        long long queryPath(int u, int v){
            if(pos[u] < pos[v]) swap(u,v);
            // now u comes after v in the pos, so we need to climb u
            if(headOfChain[u] == headOfChain[v]){
                return Seg.query(pos[v], pos[u]);
            }
            return Seg.query(pos[headOfChain[u]], pos[u]) + queryPath(parents[headOfChain[u]], v);
        }

        void updateNodeTo(int node, int val){             
            Seg.updateTo(pos[node],val);
        }
        
        void buildHLD(int cur, int parent = -1){
            pos[cur] = timer++;
            v[pos[cur]] = val[cur];
            for(int neighbour : G[cur]){
                if(neighbour == parent)
                    continue;
                headOfChain[neighbour] = ( neighbour == G[cur][0] ) ? headOfChain[cur] : neighbour;
                buildHLD(neighbour,cur);
            }
        }

        void dfs(int cur, int parent=-1){
            for(int &neighbour : G[cur]){
                if(neighbour == parent){
                    continue;
                }
                dfs(neighbour,cur);
                parents[neighbour] = cur;
                sz[cur] += sz[neighbour];
                // Just making sure that the first element in the adj list is the heaviest neighbour =p
                // Also, making sure that we are not considering the parent the heaviest
                if(sz[neighbour] > sz[G[cur][0]] || (G[cur][0] == parent)){
                    swap(neighbour, G[cur][0]);
                }
            }
        }
};