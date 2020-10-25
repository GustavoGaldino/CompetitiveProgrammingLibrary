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