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
                sort(temp.begin(),temp.end());
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