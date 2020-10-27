class DSU{
    public:
        vector<int> sz;
        vector<int> dsu;
        int n;
        DSU(int n){
            this->n=n;
            sz.resize(n,1);
            dsu.resize(n);
            iota(dsu.begin(),dsu.end(),0);
        }
        
        int find(int i){
            if(i != dsu[i])
                dsu[i] = find(dsu[i]);
            return dsu[i];
        }
        void unite(int a, int b){
            a = find(a);
            b = find(b);
            if(a==b)
                return;
            // we need to merge the smaller component into the bigger one
            if(sz[a] > sz[b]){
                swap(a,b);
            }
            // now "a" belongs to the smaller component
            dsu[a] = b;
            sz[b] += sz[a];
        }

        int countComponents(){
            int cnt = 0;
            for(int i = 0 ; i < n ; i++){
                cnt += (i==dsu[i]);
            }
            return cnt;
        }
};