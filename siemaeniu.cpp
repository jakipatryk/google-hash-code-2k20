#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <random>

typedef long long ll;

ll score = 0;
std::unordered_map<ll, bool> was_used;
float param_score = 1.0;
float param_t = 1.0;

struct Lib
{
    ll id;
    ll N;
    ll T;
    ll M;
    ll possible_score;
    // vector of (score, id)
    std::vector<std::pair<ll, ll>> books;
    Lib() {}
    Lib(ll _id, ll _N, ll _T, ll _M, std::vector<std::pair<ll, ll>> &_books, ll _ps) : id(_id), N(_N), T(_T), M(_M), possible_score(_ps)
    {
        books = std::move(_books);
    }
};

struct comp
{
    bool operator()(const Lib &l1, const Lib &l2)
    {
        /* for test D:
        return l1.possible_score > l2.possible_score;
        */
        return (param_score * (1.0 / (float)l1.possible_score) + param_t * (float)l1.T) < (param_score * (1.0 / (float)l2.possible_score) + param_t * (float)l2.T);
    }
};

// returns vector of ids of books to take from given lib
std::pair<std::vector<ll>, ll> use_books(const Lib &lib, ll day, const std::vector<ll> scores, ll end_day)
{
    std::vector<ll> book_ids;
    ll books_taken = 0;
    ll books_score = 0;
    for (const auto &book : lib.books)
    {
        if (books_taken < (end_day - day) * (lib.M))
        {
            if (was_used.find(book.second) == was_used.end())
            {
                book_ids.push_back(book.second);
                score += book.first;
                was_used[book.second] = true;
                books_taken++;
                books_score += book.first;
            }
        }
        else
        {
            break;
        }
    }
    return std::make_pair(book_ids, books_score);
}

void calculate_possible_scores(std::vector<Lib> &libs, ll current_day, ll max_day, ll start = 0)
{
    for (ll i = start; i < libs.size(); i++)
    {
        auto &lib = libs[i];
        ll possible_score = 0;
        ll available_days = max_day - current_day - lib.T;
        ll available_books = std::min(lib.M * available_days, lib.N);
        for (ll k = 0; k < available_books; k++)
        {
            if (was_used.find(lib.books[k].second) == was_used.end())
                possible_score += lib.books[k].first;
        }
        lib.possible_score = possible_score;
    }
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    // different ranges for different tests
    // test F: dis_score(100000.0, 1000000.0); dis_t(0.01, 0.1)
    std::uniform_real_distribution<float> dis_score(10.0, 100.0);
    std::uniform_real_distribution<float> dis_t(100.0, 500.0);

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
        std::vector<std::pair<ll, ll>> books(N);
        for (ll j = 0; j < N; j++)
        {
            ll tmp;
            std::cin >> tmp;
            books[j] = std::make_pair(S[tmp], tmp);
        }
        std::sort(books.begin(), books.end());
        std::reverse(books.begin(), books.end());
        libs[i] = Lib(i, N, T, M, books, 0);
    }
    calculate_possible_scores(libs, 0, D);
    // vector of tuples (lib, books_taken)
    std::vector<std::pair<Lib, std::vector<ll>>> best_result;
    ll best_score = 0;
    ll best_num_of_libs = 0;
    for (int i = 0; i < 6 /* for some tests more */; i++)
    {
        was_used.clear();
        score = 0;
        ll current_day = 0;
        ll num_of_libs = 0;
        std::vector<std::pair<Lib, std::vector<ll>>> result;
        param_score = dis_score(gen);
        param_t = dis_t(gen);
        std::sort(libs.begin(), libs.end(), comp());
        ll cnt = 0;
        for (ll k = 0; k < libs.size(); k++)
        {
            /* for test D;
            if (k % 20 == 0)
            {
                calculate_possible_scores(libs, current_day, D, k);
                std::sort(libs.begin() + k, libs.end(), comp());
            }
            */
            const auto &lib = libs[k];
            current_day += lib.T;
            if (current_day <= D)
            {
                auto tmp = use_books(lib, current_day, S, D);
                ll threshold = 1 /* for test f: 90000*/;
                if (tmp.second < threshold)
                {
                    current_day -= lib.T;
                    score -= tmp.second;
                    continue;
                }
                result.push_back(std::make_pair(lib, tmp.first));
                num_of_libs++;
            }
            else
            {
                break;
            }
            cnt++;
        }
        if (score > best_score)
        {
            best_score = score;
            best_num_of_libs = num_of_libs;
            best_result = std::move(result);
        }
    }

    std::cout << best_num_of_libs << std::endl;
    for (auto &pair : best_result)
    {
        std::cout << pair.first.id << " " << pair.second.size() << std::endl;
        for (auto id : pair.second)
        {
            std::cout << id << " ";
        }
        std::cout << std::endl;
    }
    std::cerr << "SCORE: " << best_score << std::endl;
}
