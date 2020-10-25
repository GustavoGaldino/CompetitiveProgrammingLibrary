class SparseTable{
    public:
        int n;
        vector<int> v;
        vector<int> lgs;
        vector<vector<int>> sparseTable;
        SparseTable(vector<int> v){
            this->n = (int)v.size();
            this->v=v;
            build();
        }
 
        void build(){
            int m = log2(n)+1;
            lgs.resize(n+1,-1);
            int i = 0;
            for(int cur = 1 ; cur <= n ; cur = (cur <<1)){
                lgs[cur] = i;
                i++;
            }
            lgs[0] = 0;
            for(int i = 1 ; i <= n ; i++){
                if(lgs[i] == -1){
                    lgs[i] = lgs[i-1];
                }
            }
            sparseTable.resize(m, vector<int>(n));
            for(int i = 0 ; i < n ; i++){
                sparseTable[0][i] = v[i];
            }
            for(int j = 1 ; j < m ; j++){
                for(int i = 0 ; i < n ; i++){
                    sparseTable[j][i] = sparseTable[j-1][i];
                    if(i + (1<<(j-1)) - 1 < n){
                        sparseTable[j][i] = min(sparseTable[j][i], sparseTable[j-1][i + (1<<(j-1))]);
                    }
                }
            }
        }
 
        int get(int l, int r){
            int sz = r - l + 1;
            return min(sparseTable[lgs[sz]][l], sparseTable[lgs[sz]][r-((1<<lgs[sz]))+1]);
        }
};