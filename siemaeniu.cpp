#include <iostream>
#include <vector>

typedef long long ll;

struct Lib
{
    ll N;
    ll T;
    ll M;
    std::vector<ll> books;
    Lib(ll _N, ll _T, ll _M, std::vector<ll> &_books) : N(_N), T(_T), M(_M)
    {
        books = std::move(_books);
    }
};

int main()
{
    ll B, L, D;
    std::cin >> B >> L >> D;
    std::vector<ll> S(B);
    std::vector<Lib> libs(L);
    for (ll i = 0; i < B; i++)
    {
        std::cin >> S[i];
    }
    for (ll i = 0; i < L; i++)
    {
        ll N, T, M;
        std::cin >> N >> T >> M;
        std::vector<ll> books(N);
        for (ll j = 0; j < N; j++)
        {
            std::cin >> books[j];
        }
        libs[i] = Lib(N, T, M, books);
    }
}
