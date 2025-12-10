#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n,a,t;
long long ans;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        vector<int> v;
        ans=0;
        for(int i=0;i<2n;i++){
            cin>>a;
            v.push_back(a);
        }
        sort(v.begin(),v.end());
        for(int i=n;i<2n;i++){
            ans+=v[i];
        }
        for(int i=0;i<n;i++){
            ans-=v[i];
        }
        cout<<ans<<'\n';
    }
}