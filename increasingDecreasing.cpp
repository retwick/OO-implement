int Solution::longestSubsequenceLength(const vector<int> &A) {
    int n =A.size();
    vector <int> In(A.size(),1);
    vector <int> Dec(A.size(),1);
    
    for(int i=1; i<n; ++i){
        for(int j=i-1; j>=0; --j){
            if(A[i]>A[j]){
                In[i] =max(In[i],In[j]+1);
            }
        }
    }
    
    for(int i=n-2; i>=0; --i){
        for(int j=i+1; j<n; ++j){
            if(A[i]>A[j]){
                Dec[i] = max(Dec[i], Dec[j]+1);
            }
        }
    }
    
    int mx = 0;
    for(int i = 0; i <A.size()-1; ++i){
        mx = max(mx,In[i]+Dec[i]-1);
    }
    return mx;
}
