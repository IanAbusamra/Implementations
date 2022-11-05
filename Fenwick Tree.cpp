struct Fenwick {
    int n; 
    vector<ll> bit;
    Fenwick(int _n) {
        n = _n + 2;
        bit.resize(_n + 1, 0);
    }
    void add(int i, ll k) {
        while(i < n) {
            bit[i] += k;
            i += i & -i;
        }
    }
    ll sum(int i) {
        ll sum = 0;
        while(i > 0) {
            sum += bit[i];
            i -= i & -i;
        }
        return sum;
    }
}
