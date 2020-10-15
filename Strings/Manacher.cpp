class Manacher{
    public:
        string s;
        int n;
        vector<int> odd;
        vector<int> even;
        Manacher(string s){
            this-> s = s;
            this->n = s.size();
            odd.resize(n,0);
            even.resize(n);
            build();
        }
        void buildOdd(){
            int l = 0;
            int r = -1;
            for(int i = 0 ; i < n ; i++){
                if(i > r){
                    for(int k = 0 ; (i - k >= 0) && (i + k < n) ; k++){
                        if(s[i-k] == s[i+k]){
                            l = i - k;
                            r = i + k;
                            odd[i]++;
                        }
                        else{
                            l = i - k + 1;
                            r = i + k - 1;
                            break;
                        }
                    }
                }
                else{
                    odd[i] = min(odd[l + (r-i)], (r-i) );
                    for(int k = odd[i] ; (i-k >= 0) && (i+k<n) ; k++){
                        if(s[i-k] == s[i+k]){
                            l = i - k;
                            r = i + k;
                            odd[i]++;
                        }
                        else{
                            l = i - k + 1;
                            r = i + k - 1;
                            break;
                        }
                    }
                }
            }
        }
        void buildEven(){
            int l = 0;
            int r = -1;
            for(int i = 0 ; i < n ; i++){
                if(i > r){
                    for(int k = 1 ; (i-k >= 0) && (i+k-1 < n) ; k++){
                        if(s[i-k] == s[i+k-1]){
                            l = i-k;
                            r = i+k-1;
                            even[i]++;
                        }
                        else
                            break;
                    }
                }
                else{
                    // por que l + (r-1) + 1 e não l + (r-1)???
                    even[i] = min(even[l + (r-i) + 1], r-i+1);
                    for(int k = even[i]+1; (i-k >= 0) && (i+k-1 < n) ; k++){
                        if(s[i-k] == s[i+k-1]){
                            l = i -k;
                            r = i + k -1;
                            even[i]++;
                        }
                        else
                            break;
                    }
                }
            }            
        }
        void build(){
            buildOdd();
            buildEven();
        }

        int longestPalindromicSubstringLength(){
            int ans = 1;
            for(int cur : odd){
                ans = max(ans, cur*2 - 1);
            }
            for(int cur : even){
                ans = max(ans, 2 * cur);
            }
            return ans;
        }
};