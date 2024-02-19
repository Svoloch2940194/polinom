#include "Map.h"
#include <gtest.h>
#include <string>

TEST(Map, can_create_map_with_simple_type_and_add_element)
{
    Map<ll, ll> ma;
    ma[1] = 1;
    ASSERT_NO_THROW(ma[1]);
}

TEST(Map, can_create_map_with_no_simple_type_ans_add_element)
{
    Map<ll,string> ma;
    ma[1] = "a";
    ma[2] = "b";
    ASSERT_NO_THROW(ma[1]);
}

TEST(Map, new_map_with_simple_type_check_change_value)
{
    Map<ll, ll> ma;
    for (ll i = 0; i < 100; ++i)  ma[i] = i;
    for (ll i = 0; i < 100; ++i)  ma[i] += 101;

    EXPECT_EQ(156, ma[55]);
}

TEST(Map, new_map_with_no_simple_type_check_change_value)
{
    Map<string, ll> ma;
    
    ma["a"] = 126;
    ma["a"] += 100;

    EXPECT_EQ(226, ma["a"]);
}

TEST(Map, test_size)
{
    Map<ll, ll> ma;
    EXPECT_EQ(0, ma._size());
}

TEST(Map, test_size_add_element)
{
    Map<ll, ll> ma;
    ma[0] = 0;
    ma[1] = 1;
    ma[2] = 2;
    EXPECT_EQ(3, ma._size());
}

TEST(Map, test_iterator)
{
    Map<ll, ll> ma;
    for (ll i = 0; i < 1000; ++i) ma[i] = rand() % 1000;

    ASSERT_NO_THROW(for (auto i : ma););
}

TEST(Map, test_begin)
{
    Map<ll, ll> ma;
    EXPECT_EQ(1, ma.begin() == nullptr);
}

TEST(Map, test_begin_with_some_element)
{
    Map<ll, ll> ma;
    ma[0]=1;
    ma[2]=2;
    ma[1]=0;
    EXPECT_EQ(0, ma.begin() == nullptr);
}

TEST(Map, test_end)
{
    Map<ll, ll> ma;
    EXPECT_EQ(1, ma.end() == nullptr);
}

TEST(Map, test_end_with_some_element)
{
    Map<ll, ll> ma;
    ma[0] = 1;
    ma[2] = 2;
    ma[1] = 0;
    EXPECT_EQ(1, ma.end() == nullptr);
}

TEST(Map, test_iterator_with_minus)
{
    Map<ll, ll> ma;
    ma[0] = 0;
    ma[-100] = 1;
    ma[-50] = 2;
    ma[100] = 3;
    ma[4] = 4;
    auto x = ma.begin();

    ++x;
    ++x;
    ++x;
    --x;

    ASSERT_NO_THROW(--x);
}