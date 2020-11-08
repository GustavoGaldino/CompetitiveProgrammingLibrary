vector<int> smp;

void buildSMP(int n){
    smp.resize(n+1,-1);
    for(int i = 2 ; i <= n ; i++){
        if(smp[i] == -1){
            for(int j = i ; j <= n ; j+=i){
                if(smp[j] == -1){
                    smp[j] = i;
                }
            }
        }
    }
}