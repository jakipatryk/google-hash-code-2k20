#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

typedef long long ll;

struct comp
{
    bool operator()(const Lib &l1, const Lib &l2)
    {
        // eq -> false, lt -> true
        return l1.T < l2.T;
    }
};

struct Lib
{
    ll id;
    ll N;
    ll T;
    ll M;
    std::vector<ll> books;
    Lib(ll _id, ll _N, ll _T, ll _M, std::vector<ll> &_books) : id(_id), N(_N), T(_T), M(_M)
    {
        books = std::move(_books);
    }
};

// returns vector of ids of books to take from given lib
std::vector<ll> use_books(const Lib &lib, ll day, const std::vector<ll> scores, ll end_day)
{
    std::vector<ll> book_ids;
    ll books_taken = 0;
    for (auto book : lib.books)
    {
        if (books_taken < (end_day - day) * (lib.M))
        {
            book_ids.push_back(book);
        }
        else
        {
            break;
        }
        books_taken++;
    }
    return book_ids;
}

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
        libs[i] = Lib(i, N, T, M, books);
    }
    std::sort(libs.begin(), libs.end(), comp());
    ll current_day = 0;
    ll num_of_libs = 0;
    // vector of tuples (lib, books_taken)
    std::vector<std::pair<Lib, std::vector<ll>>> result;
    for (auto &lib : libs)
    {
        current_day += lib.T;
        if (current_day < D)
        {
            num_of_libs++;
            result.push_back(std::make_pair(lib, use_books(lib, current_day, S, D)));
        }
        else
        {
            break;
        }
    }
    std::cout << num_of_libs << std::endl;
    for (auto &pair : result)
    {
        std::cout << pair.first.id << " " << pair.second.size() << std::endl;
        for (auto id : pair.second)
        {
            std::cout << id << " ";
        }
        std::cout << std::endl;
    }
}
