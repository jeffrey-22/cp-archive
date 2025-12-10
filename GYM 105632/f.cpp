#include<bits/stdc++.h>
using namespace std;
long long a,b,n,k,q,s,c;
vector<pair<long long, long long>> v;
vector<long long> f;
int main(){
    cin>>n>>k>>q;
    for(int i=0;i<n;i++){
        cin>>a>>b;
        s+=b;
        a--;
        v.push_back({a,b});
    }
    for(int i=0;i<n;i++){
        c=max(c,v[i].first)+v[i].second;
        f.push_back(c-1);
    }
    for(int i=0;i<n;i++){
        c=max(c,v[i].first+k)+v[i].second;
        f.push_back(c-1);
    }
    for(int i=0;i<q;i++){
        cin>>a>>b;
        b--;
        if(s>k){
            if(a==1){
                cout<<f[b]/k+1<<' '<<(f[b])%k+1<<'\n';
            }
            else{
                long long t=(a-2)*s+f[n+b];
                cout<<t/k+1<<' '<<(t)%k+1<<'\n';
            }
        }
        else{
            if(a==1){
                cout<<f[b]/k+1<<' '<<f[b]%k+1<<'\n';
            }
            else{
                cout<<f[n+b]/k+a-1<<' '<<f[n+b]%k+1<<'\n';
            }
        }
    }
}