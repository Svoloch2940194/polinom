#pragma once
#include <string>
#include "Map.h"

struct step
{
    ll x, y, z;

    bool operator<(const step& a) const
    {
        if (x < a.x) return true;
        else
        {
            if (x > a.x) return false;
            else
            {
                if (y < a.y) return true;
                else
                {
                    if (y > a.y) return false;
                    else
                    {
                        if (z < a.z) return true;
                        else return false;
                    }
                }
            }
        }
    }

    bool operator>(const step& a) const
    {
        if (x > a.x) return true;
        else
        {
            if (x < a.x) return false;
            else
            {
                if (y > a.y) return true;
                else
                {
                    if (y < a.y) return false;
                    else
                    {
                        if (z > a.z) return true;
                        else return false;
                    }
                }
            }
        }
    }

    bool operator==(const step& a) const { return x == a.x && y == a.y && z == a.z; }
    bool operator!=(const step& a) const { return x != a.x || y != a.y || z != a.z; }

    step operator*(step a) const
    {
        step ans;

        ans.x = x + a.x;
        ans.y = y + a.y;
        ans.z = z + a.z;
        return ans;
    }
};

ll pow2(ld x, ll step_x)
{
    if (step_x == 0) return 1;
    else
    {
        if (step_x % 2) return pow2(x, step_x - 1)* x;
        else return pow2(x, step_x / 2)* pow2(x, step_x / 2);
    }
}

struct point
{
    ld x, y, z;

    point(ll x1, ll y1, ll z1) { x = x1; y = y1; z = z1; }

    ll operator^(step& a) const
    {
        ll ans = 1;
        ans *= pow2(x, a.x);
        ans *= pow2(y, a.y);
        ans *= pow2(z, a.z);
        return ans;
    }
};

class Polinom
{
    struct node
    {
        pair<ld, step> value;
        node* head;

        node() { head = nullptr; }
    };

    node* head;
    size_t size;

public:

    size_t _size() { return size; }

    Polinom() 
    {
        auto x = new node;
        head = x;
        x->value.first = 0;
        x->value.second = { 0,0,0 };
        size = 0;
    }

    ~Polinom()
    {
        while (head != nullptr)
        {
            node* h = head->head;
            delete[] head;
            head = h;
        }
    }

    Polinom(const Polinom& x)
    {
        head = nullptr;
        size = x.size;
        node* h1 = x.head;
        node* h;
        while (h1 != nullptr)
        {
            if (head = nullptr)
            {
                auto n = new node;
                n->value = h1->value;
                head = n;
                h = n;
            }
            else
            {
                auto n = new node;
                n->value = h1->value;
                head = n;
                h = n;
            }
            h1 = h1->head;
        }
    }

    Polinom(Polinom&& x) noexcept
    {
        size = x.size;
        head = x.head;
        x.head = nullptr;
        x.size = 0;
    }

    Polinom(string s)
    {
        size = 0;
        head = nullptr;
        s += '+';
        Map<step, ld> step_c;
        string c = "";
        string coif = "";
        step a;
        a.x = 0;
        a.y = 0;
        a.z = 0;
        bool x = false, y = false, z = false;
        ll st = -1;
        for (auto i : s)
        {
            if (i == ' ') continue;

            if (i == '-' || i == '+' || i >= '0' && i <= '9' || i == '.')
            {
                if ((st > 0 || (!c.empty())&&(c.back() >= '0' && c.back() <= '9')) && (i == '-' || i == '+'))
                {
                    if (c == "") c = "1";
                    if (st == 1)
                    {
                        for (auto id : c) if (id == '.') throw "degree must be an integer";
                        a.x = stoll(c);
                    }
                    if (st == 2)
                    {
                        for (auto id : c) if (id == '.') throw "degree must be an integer";
                        a.y = stoll(c);
                    }
                    if (st == 3)
                    {
                        for (auto id : c) if (id == '.') throw "degree must be an integer";
                        a.z = stoll(c);
                    }
                    st = -1;
                    if (coif == "") coif = c;
                    c = "";
                    if (coif != "-0" && coif != "0" && coif != "+0") step_c[a] += stold(coif);
                    x = y = z = false;
                    a.x = a.y = a.z = 0;
                    coif = "";
                    c += i;
                }
                else
                {
                    if(!c.empty()) if ((c.back() == '+' || c.back() == '-') && (i == '-' || i == '+')) throw "error";

                    c += i;
                }
            }
            else
            {
                if (i == 'x' || i == 'y' || i == 'z')
                {
                    if (!x && !y && !z)
                    {
                        if (c == "") c = "1";
                        coif = c, c = "";
                        if (coif == "+" || coif == "-") coif += '1';
                    }
                    else
                    {
                        if (c == "") c = "1";
                        if (st == 1)
                        {
                            for (auto id : c) if (id == '.') throw "degree must be an integer";
                            a.x = stoll(c);
                        }
                        if (st == 2)
                        {
                            for (auto id : c) if (id == '.') throw "degree must be an integer";
                            a.y = stoll(c);
                        }
                        if (st == 3)
                        {
                            for (auto id : c) if (id == '.') throw "degree must be an integer";
                            a.z = stoll(c);
                        }
                        c = "";
                        st = -1;
                    }

                    if (i == 'x') st = 1, x = true;
                    if (i == 'y') st = 2, y = true;
                    if (i == 'z') st = 3, z = true;
                }
                else
                {
                    if (i == '^' || i == '*') continue;
                    else throw "unknown symbol";
                }
            }
        }

        for (auto x : step_c)
        {
            auto n = new node;
            (n->value.first) = x.second;
            (n->value.second) = x.first;
            (n->head) = head;
            head = n;
            ++size;
        }
    }

    Polinom operator=(Polinom&& x) noexcept
    {
        swap(head, x.head);
        swap(size, x.size);
        return *this;
    }

    Polinom operator=(const Polinom& x)
    {
        if (head == x.head) return *this;
        
        this->~Polinom();
        size = x.size;
        node* h = x.head;
        auto new_head = new node;
        head = new_head;
        while (true)
        {
            new_head->value.first = h->value.first;
            new_head->value.second = h->value.second;
            h = h->head;
            if (h != nullptr)
            {
                auto a = new node;
                new_head->head = a;
                new_head = a;
            }
            else break;
        }

        return* this;
    }

    bool operator==(const Polinom& x)
    {
        if (size != x.size) return false;

        node* h1 = head;
        node* h2 = x.head;

        while (h1 != nullptr)
        {
            if (h1->value.first != h2->value.first || h1->value.second != h2->value.second) return false;

            h1 = h1->head;
            h2 = h2->head;
        }

        return true;
    }

    bool operator!=(const Polinom& x) { return !(*this == x); }

    Polinom operator+(const Polinom& x)
    {
        Polinom ans;

        node* h1 = head;
        node* h2 = x.head;
        auto ans_h = new node;

        while (h1 != nullptr && h2 != nullptr)
        {
            if (h1->value.second == h2->value.second)
            {
                if (h1->value.first + h2->value.first != 0)
                {
                    if (ans.size == 0) ans.head = ans_h;
                    else
                    {
                        auto a = new node;
                        ans_h->head = a;
                        ans_h = a;
                    }
                    ++ans.size;
                    ans_h->value.second = h1->value.second;
                    ans_h->value.first = h1->value.first + h2->value.first;
                    h1 = h1->head;
                    h2 = h2->head;
                }
                else
                {
                    h1 = h1->head;
                    h2 = h2->head;
                }
            }
            else
            {
                if (h1->value.second < h2->value.second)
                {
                    if (ans.size == 0) ans.head = ans_h;
                    else
                    {
                        auto a = new node;
                        ans_h->head = a;
                        ans_h = a;
                    }
                    ++ans.size;
                    ans_h->value.second = h2->value.second;
                    ans_h->value.first = h2->value.first;
                    h2 = h2->head;
                }
                else
                {
                    if (ans.size == 0) ans.head = ans_h;
                    else
                    {
                        auto a = new node;
                        ans_h->head = a;
                        ans_h = a;
                    }
                    ++ans.size;
                    ans_h->value.second = h1->value.second;
                    ans_h->value.first = h1->value.first;
                    h1 = h1->head;
                  
                }
            }
        }

        while (h1 != nullptr)
        {
            auto del = new node;
            ans_h->head = del;
            ans_h = del;
            ++ans.size;
            ans_h->value.second = h1->value.second;
            ans_h->value.first = h1->value.first;
            h1 = h1->head;
        }

        while (h2 != nullptr)
        {
            auto del = new node;
            ans_h->head = del;
            ans_h = del;
            ++ans.size;
            ans_h->value.second = h2->value.second;
            ans_h->value.first = h2->value.first;
            h2 = h2->head;
        }

        if (ans.head == nullptr)
        {
            auto a = new node;
            a->value.first = 0;
            ans.head = a;
        }
        return ans;
    }

    Polinom operator+=(const Polinom& x)
    {
        (*this) = (*this) + x;
        return* this;
    }

    Polinom operator*(const ll& x) const
    {
        Polinom ans;
        if (x == 0) return ans;

        auto ans_h = new node;
        node* h = head;
        ans.head = ans_h;
        ans.size = size;
        while (true)
        {
            ans_h->value.second = h->value.second;
            ans_h->value.first = x * h->value.first;
            h = h->head;
            if (h != nullptr)
            {
                auto a = new node;
                ans_h->head = a;
                ans_h = a;
            }
            else break;
        }

        return ans;
    }

    Polinom operator-(const Polinom& x)
    {
        Polinom y = x * (-(1ll));
        Polinom ans = (*this) + y;
        return ans;
    }

    Polinom operator-=(const Polinom& x)
    {
        *this = *this - x;
        return* this;
    }

    Polinom operator *=(const ll& x)
    {
        (*this) = (*this) * x;
        return* this;
    }

    Polinom operator *(const Polinom& x)
    {
        Polinom ans;
        Map<step, ld> step_c;
        node* h1 = x.head;
        while (h1 != nullptr)
        {
            node* h2 = head;
            while (h2 != nullptr)
            {
                step a = h1->value.second * h2->value.second;
                if (step_c[a] == 0) step_c[a] = h1->value.first * h2->value.first;
                else step_c[a] += h1->value.first * h2->value.first;

                h2 = h2->head;
            }
            h1 = h1->head;
        }

        node* ans_h = nullptr;
        for (auto x : step_c)
        {
            if (x.second != 0)
            {
                auto n = new node;
                (n->value.first) = x.second;
                (n->value.second) = x.first;
                (n->head) = ans_h;
                ans_h = n;
                ++ans.size;
            }
        }

        ans.head = ans_h;
        return ans;
    }

    Polinom operator*=(const Polinom& x)
    {
        *this = *this * x;
        return* this;
    }

    ll operator[](const point& x)
    {
        ll ans = 0;
        node* h = head;
        while (h != nullptr)
        {
            ans += (h->value.first) * (x ^ (h->value.second));
            h = h->head;
        }

        return ans;
    }

    friend ostream& operator<<(ostream& out, Polinom& x);
    friend istream& operator>>(istream& in, Polinom& x);
};

istream& operator>>(istream& in, Polinom& x)
{
    string s;
    getline(in, s);
    Polinom ans(s);
    x = ans;
    return in;
}

ostream& operator<<(ostream& out, Polinom& x)
{
    Polinom::node* h = x.head;
    while (h != nullptr)
    {
        if (h->value.first > 0)
        {
            if (h == x.head)
            {
                if (h->value.first!= 1) out << h->value.first;
                else if (h->value.second.x == 0 && h->value.second.y == 0 && h->value.second.z == 0) out << h->value.first;
                if (h->value.second.x != 0)
                {
                    if (h->value.second.x > 1) out << "x^" << h->value.second.x;
                    else out << "x";
                }
                if (h->value.second.y != 0)
                {
                    if (h->value.second.y > 1) out << "y^" << h->value.second.y;
                    else out << "y";
                }
                if (h->value.second.z != 0)
                {
                    if (h->value.second.z > 1) out << "z^" << h->value.second.z;
                    else out << "z";
                }
            }
            else
            {
                if (h->value.first!= 1) out << "+" << h->value.first;
                else
                {
                    if (h->value.second.x == 0 && h->value.second.y == 0 && h->value.second.z == 0) out << "+" << h->value.first;
                    else out << "+";
                }
                if (h->value.second.x != 0)
                {
                    if (h->value.second.x > 1) out << "x^" << h->value.second.x;
                    else out << "x";
                }
                if (h->value.second.y != 0)
                {
                    if (h->value.second.y > 1) out << "y^" << h->value.second.y;
                    else out << "y";
                }
                if (h->value.second.z != 0)
                {
                    if (h->value.second.z > 1) out << "z^" << h->value.second.z;
                    else out << "z";
                }
            }
        }
        else
        {
            if (h->value.first != -1) out << h->value.first;
            else
            {
                if (h->value.second.x == 0 && h->value.second.y == 0 && h->value.second.z == 0) out << h->value.first;
                else out << "-";
            }

            if (h->value.second.x != 0)
            {
                if (h->value.second.x > 1) out << "x^" << h->value.second.x;
                else out << "x";
            }
            if (h->value.second.y != 0)
            {
                if (h->value.second.y > 1) out << "y^" << h->value.second.y;
                else out << "y";
            }
            if (h->value.second.z != 0)
            {
                if (h->value.second.z > 1) out << "z^" << h->value.second.z;
                else out << "z";
            }
        }
        h = h->head;
    }

    return out;
}