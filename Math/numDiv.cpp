class numDiv{
	public:
		vector<int> divs;
		vector<int> smp;
		vector<int> freq;
		numDiv(int n){
			divs.resize(n+1,1);
			smp.resize(n+1,-1);
			freq.resize(n+1,1);
			for(int i = 2; i <= n; i++){
				if(smp[i] == -1){
					smp[i] = i;
					for(int j = 2*i ; j <= n; j+=i){
						if(smp[j] == -1){
							smp[j] = i;
							int aux = j/i;
							if(smp[aux] == i){
								freq[j] = freq[aux] + 1;
							}
						}
					}
				}
			}
			for(int i = 2 ; i <= n ; i++){
				if(smp[i] == i){
					divs[i] = 2;
				}
				else{
					divs[i] = (divs[i/(smp[i])] * (freq[i]+1))/(freq[i]);
				}
			}
		}
		int get(int i){
			return this->divs[i];
		}
};