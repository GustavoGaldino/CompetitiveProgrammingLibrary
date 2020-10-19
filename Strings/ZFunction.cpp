 class ZFunc{
    public:
        string s;
        string p;
        int n;
        vector<int> Z;
        ZFunc(string s, string p){
            this->p = p;
            if(p != ""){
                this->s = p + '$' + s;
            }
            else
                this->s = s;
            build();
        }

        void build(){
            n = s.size();
            Z.resize(n);
            int leftBoundarie = 0;
            int rightBoundarie = 0;
            for(int i = 1 ; i < n ; i++){
                if(i <= rightBoundarie){
                    Z[i] = min(rightBoundarie-i+1, Z[i-leftBoundarie]);
                }
                while(i + Z[i] < n && s[i+Z[i]] == s[Z[i]]){
                    Z[i]++;
                }
                if(i + Z[i] - 1 > rightBoundarie){
                    rightBoundarie = i + Z[i] - 1;
                    leftBoundarie = i;
                }
            }
        }

        int patternFrequency(){
            int cnt = 0;
            for(int i = 1 ; i <n ; i++){
                if(Z[i] == p.size())
                    cnt++;
            }
            return cnt;
        }

        vector<int> patternIndexes(){
            vector<int> indexes;
            for(int i = 1 ; i < n ; i++){
                if(Z[i] == p.size())
                    indexes.push_back(i - p.size() - 1);
            }
            return indexes;
        }

        string smallestCyclicPrefix(){
            stack<int> divisors;
            for(int i = 1 ; i <= sqrt(n) ; i++){
                if(n%i == 0){
                    if(Z[i] + i == n)
                        return s.substr(0,i);
                    if(i!=1)
                        divisors.push(i);
                }
            }
            while(!divisors.empty()){
                int i = divisors.top();
                divisors.pop();
                int div = n/i;
                if(Z[div] + div == n)
                    return s.substr(0,div);
            }
            return s.substr(0,n);
        }
};