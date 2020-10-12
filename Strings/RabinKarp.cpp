class Hashing{
    public:
        long long mod;
        long long base;
        vector<long long> pot;
        vector<long long> hashVec;
        vector<long long> potRev;
        vector<long long> hashRev;
        string rev;
        string s;
        int n;
        Hashing(long long mod, long long base, string s){
            this->mod = mod;
            this->base = base;
            this->s = s;
            this->n = (int)s.size();
            build();
        }
        void build(){
            pot.resize(n);
            hashVec.resize(n);
            pot[0] = 1;
            hashVec[0] = s[0];
            for(int i = 1 ; i < n ; i++){
                pot[i] = (pot[i-1] * base)%mod;
                hashVec[i] = (hashVec[i-1]*base + s[i])%mod;
            }
        }

        void buildForReversedString(){
            this->rev = s;
            reverse(rev.begin(), rev.end());
            potRev.resize(n);
            hashRev.resize(n);
            potRev[0] = 1;
            hashRev[0] = rev[0];
            for(int i = 1 ; i < n ; i++){
                potRev[i] = (potRev[i-1] * base)%mod;
                hashRev[i] = (hashRev[i-1]*base + rev[i])%mod;
            }
        }

        long long getKey(int l, int r){
            if(l == 0)
                return hashVec[r];
            else
                return ((hashVec[r] - (hashVec[l-1]*pot[r-l+1])%mod) + mod)%mod;
        }

        long long getKeyRev(int l, int r){
            if(l == 0)
                return hashRev[r];
            else
                return ((hashRev[r] - (hashRev[l-1]*potRev[r-l+1])%mod) + mod)%mod;
        }

        bool isPalindrome(int l, int r){
            return (getKey(l,r) == getKeyRev(n-1-r, n-1-l));
        }
};