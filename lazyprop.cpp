#include <bits/stdc++.h>
using namespace std;
#define flash ios_base::sync_with_stdio(0);cin.tie(NULL);
#define int long long
#define frl(i,a,b) for(int i=a;i<b;i++)
#define MOD 1000000007
#define pi (3.141592653589)
#define vs vector<string>
#define vi vector<int>
#define vc vector<char>
#define vpii vector<pair<int, int>>
#define vvii vector<vector<int, int>>
#define pb push_back

class ST{
    public: 
    vector<int> seg, lazy;

    public:
        ST(int n)
        {
            seg.resize(4*n+1);
            lazy.resize(4*n+1);
        }

    void build(int ind, int low, int high, vector<int>& arr)
    {
        if(low==high)
        {
            seg[ind]=arr[low];
            return;
        }

        int mid = low + (high-low)/2;
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);

        seg[ind] = seg[2*ind+1] + seg[2*ind+2];
    }

    int query(int ind, int low, int high, int l, int r, vector<int>& arr)
    {
        // update prev remaining updates && propagate downwards
        if(lazy[ind] != 0)
        {
            seg[ind] += (high-low+1)*lazy[ind];

            // propagate downwards
            if(low!=high)
            {
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }


        // complete overlap  l low high, r
        if(l<=low && high<=r)
        {
            return seg[ind];
        }
        // no overlap
        if(r<low || l>high)
        {
            return 0;
        }
        // partial overlap
        else{

            int mid = low + (high-low)/2;

            int left = query(2*ind+1, low, mid, l, r, arr);
            int right = query(2*ind+2, mid+1, high, l, r, arr);

            return seg[ind] = left+right;
        }
    }

    void update(int ind, int low, int high, int l, int r, int val, vector<int>& arr)
    {

        // update prev remaining updates && propagate downwards
        if(lazy[ind] != 0)
        {
            seg[ind] += (high-low+1)*lazy[ind];

            // propagate downwards
            if(low!=high)
            {
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // no overlap
        if(r<low || l>high)
        {
            return;
        }

        // complete overlap  l low high, r
        if(l<=low && high<=r)
        {
            seg[ind] += (high-low+1)*val;
            if(low!=high)
            {
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }

            return;
        }

        // partial overlap
        else
        {
            int mid = low + (high-low)/2;

            update(2*ind+1, low, mid, l, r, val, arr);
            update(2*ind+2, mid+1, high, l, r, val, arr);

            seg[ind] = seg[2*ind+1] + seg[2*ind+2];
        }
    }
};

void solve()
{
    int n;
    cin>>n;

    vector<int> arr;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        arr.pb(x);
    }
    int q;
    cin>>q;

    ST sgt1(n);
    sgt1.build(0, 0, n-1, arr);

    while(q--)
    {
        int type;
        cin>>type;

        if(type==1){
            // update 
            int l,r,val;
            cin>>l>>r>>val;

            sgt1.update(0, 0, n-1, l-1, r-1, val, arr);
        }
        else{
            int l , r;
            cin>>l>>r;

            int ans = sgt1.query(0, 0, n-1, l-1, r-1, arr);
            cout<<"ans: ";
            cout<<ans<<endl;
        }
    }


}


int32_t main()
{
flash
int tt=1;
// cin>>tt;
while(tt--)
{
solve();
}
return 0;
}