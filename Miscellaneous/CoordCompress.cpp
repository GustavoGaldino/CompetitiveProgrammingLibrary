#include <bits/stdc++.h>
using namespace std;

vector<int> coordCompress(vector<int> a){
    int cur = 0;
    int n = a.size();
    vector<int> coordCompress(n);
    map<int,int> aux;
    vector<int> b(n);
    for(int i = 0  ; i< n ; i++){
        b[i] = a[i];
    }
    sort(a.begin() , a.end());
    for(int i = 0; i < n ; i++){
        if(i > 0 && (a[i] == a[i-1])){
            continue;
        }
        int element = a[i];
        aux[element] = cur;
        cur++;
    }
    for(int i = 0 ; i < n ; i++){
        coordCompress[i] = aux[b[i]];
    }
    return coordCompress;
}

int main(){
    vector<int> a{21,3,40,2,1,0,-1,30};
    vector<int> u = coordCompress(a);
    for(int cur : u){
        cout << cur << " ";
    }
    cout << endl;
    return 0;
}