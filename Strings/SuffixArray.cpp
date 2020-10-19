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
            int m = v.size();
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
            vector<int> acSum1(firstBuckets);
            vector<int> acSum2(secondBuckets);
            acSum1[0] = count1[0];
            acSum2[0] = count2[0];
            for(int i = 1 ; i < max(firstBuckets,secondBuckets); i++){
                if(i < firstBuckets){
                    acSum1[i] = acSum1[i-1] + count1[i];
                }
                if(i < secondBuckets){
                    acSum2[i] = acSum2[i-1] + count2[i];
                }
            }
            vector<pair<pair<int,int>,int>> temp = v;
            int i = 0;
            for(pair<pair<int,int>,int> p : v){
                if(p.first.second > 0){
                    temp[acSum1[p.first.second-1]] = p;
                    acSum1[p.first.second-1]++;
                }
                else{
                    temp[i] = p;
                    i++;
                }
            }
            i = 0;
            for(pair<pair<int,int>,int> p : temp){
                if(p.first.first > 0){
                    v[acSum2[p.first.first-1]] = p;
                    acSum2[p.first.first-1]++;
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
};