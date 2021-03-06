class SuffixArray{
    public:
        string s;
        int n;
        vector<int> suffixArray;
        vector<int> equivalentClasses;
        SuffixArray(string s){
            this->s = s + '$';
            this->n = this->s.size();
            suffixArray.resize(n);
            equivalentClasses.resize(n);
            build();
        }
        void radixSort(vector<pair<pair<int,int>,int>> &v){
            int firstBuckets = 0;
            int secondBuckets = 0;
            for(pair<pair<int,int>,int> p : v){
                firstBuckets = max(firstBuckets+1, p.first.second);
                secondBuckets = max(secondBuckets+1, p.first.first);
            }
            vector<int> count1(firstBuckets);
            vector<int> count2(secondBuckets);
            for(pair<pair<int,int>,int> p : v){
                count1[p.first.second]++;
                count2[p.first.first]++;
            }
            for(int i = 1 ; i < firstBuckets; i++){
                count1[i] += count1[i-1];
            }
            for(int i = 1 ; i < secondBuckets ; i++){
                count2[i] += count2[i-1];
            }
            vector<pair<pair<int,int>,int>> temp = v;
            int i = 0;
            for(pair<pair<int,int>,int> p : v){
                if(p.first.second > 0){
                    temp[count1[p.first.second-1]] = p;
                    count1[p.first.second-1]++;
                }
                else{
                    temp[i] = p;
                    i++;
                }
            }
            i = 0;
            for(pair<pair<int,int>,int> p : temp){
                if(p.first.first > 0){
                    v[count2[p.first.first-1]] = p;
                    count2[p.first.first-1]++;
                }
                else{
                    v[i] = p;
                    i++;
                }
            }
        }
        void build(){
            // k == 0
            vector<pair<char,int>> toSort(n);
            for(int i = 0 ; i < n ; i++){
                toSort[i] = {s[i], i};
            }
            sort(toSort.begin(), toSort.end());
            for(int i = 0, j = 0; i < n ; i++){
                if(i == 0)
                    equivalentClasses[toSort[i].second] =  j;
                else{
                    bool isEqual = (toSort[i].first == toSort[i-1].first);
                    if(isEqual)
                        equivalentClasses[toSort[i].second] = j;
                    else
                        equivalentClasses[toSort[i].second] = ++j;
                }
            }
            vector<pair<pair<int,int>,int>> temp;
            for(int k = 1 ; (1<<k) < 2*n ; k++){
                temp.clear();
                temp.resize(n);
                for(int i = 0 ; i < n ; i++){
                    temp[i] = {{equivalentClasses[i], equivalentClasses[(i+(1<<(k-1)))%n]},i};
                }
                radixSort(temp);
                for(int i = 0, j = 0 ; i <  n ; i++){
                    if(i==0)
                        equivalentClasses[temp[i].second] = j;
                    else{
                        bool isEqual = ((temp[i].first.first == temp[i-1].first.first)&&(temp[i].first.second ==temp[i-1].first.second));
                        if(isEqual)
                            equivalentClasses[temp[i].second] = j;
                        else
                            equivalentClasses[temp[i].second] = ++j;
                    }
                }
            }
            for(int i = 0 ; i < n ; i++){
                suffixArray[i] = temp[i].second;
            }
        }
        bool isSubstring(string p){
            int sz = p.size();
            int l = 0;
            int r = n-1;
            while(r-l>1){
                int m =(r+l)/2;
                for(int i = 0, cur = suffixArray[m] ; i < sz ; i++, cur++){
                    if(cur == n){
                        cur =0;
                    }
                    if(s[cur] > p[i]){
                        r = m;
                        break;
                    }
                    else if(s[cur] < p[i]){
                        l = m;
                        break;
                    }
                    else if(i == sz-1){
                        return true;
                    }
                }
            }
            for(int k = l ; k <= r ; k++){
                for(int i = 0, cur = suffixArray[k] ; i < sz ; i++, cur++){
                    if(cur == n){
                        cur =0;
                    }
                    if((s[cur] > p[i]) || (s[cur] < p[i])){
                        break;
                    }
                    else if(i == sz-1){
                        return true;
                    }
                }
            }
            return false;
        }
};