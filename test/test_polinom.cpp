#include "polinom.h"
#include <gtest.h>

TEST(Polinom, can_create_null_polinom)
{
	ASSERT_NO_THROW(Polinom x;);
}

TEST(Polinom, can_create_polinom_not_null_size_and_int_c)
{
	Polinom x("1.2x^2+1.1");
	//Polinom x("x^2+1");

	EXPECT_EQ(2, x._size());
}

TEST(Polinom, can_create_polinom_not_null_size_and_double_c)
{
	Polinom x("1.2x^2+1.1");

	EXPECT_EQ(2, x._size());
}

TEST(Polinom, can_eqals_polinoms)
{
	Polinom x("x+1");
	Polinom y("x+1");
	ASSERT_NO_THROW(x == y);
}

TEST(Polinom, can_eqals_polinoms_2)
{
	Polinom x("x+1");
	Polinom y("x+1");
	EXPECT_EQ(1, x == y);
}

TEST(Polinom, can_not_eqals_polinoms)
{
	Polinom x("x+1");
	Polinom y("y+1");
	ASSERT_NO_THROW(x != y);
}

TEST(Polinom, can_not_eqals_polinoms_2)
{
	Polinom x("x+1");
	Polinom y("y+1");
	EXPECT_EQ(1, x != y);
}

TEST(Polinom, can_add_polinom)
{
	Polinom x("x+1");
	Polinom y("y+1");
	ASSERT_NO_THROW(x + y);
}

TEST(Polinom, can_add_polinom_2)
{
	Polinom x("x+1");
	Polinom y("y+1");
	Polinom z("x+y+2");
	EXPECT_EQ(1,x + y == z);
}

TEST(Polinom, can_add_polinom_3)
{
	Polinom x("x+1");
	Polinom y("y+1");
	Polinom z("x+y+2");
	x += y;
	EXPECT_EQ(1, x == z);
}

TEST(Polinom, can_work_with_bad_steps)
{
	ASSERT_ANY_THROW(Polinom x("x^1.2"));
}

TEST(Polinom, can_sub_polinom)
{
	Polinom x("x+1");
	Polinom y("y+1");
	ASSERT_NO_THROW(x - y);
}

TEST(Polinom, can_sub_polinom_2)
{
	Polinom x("x+1");
	Polinom y("y+1");
	Polinom z("x-y");
	EXPECT_EQ(1, x - y == z);
}

TEST(Polinom, can_sub_polinom_3)
{
	Polinom x("x+1");
	Polinom y("y+1");
	Polinom z("x-y");
	x -= y;
	EXPECT_EQ(1, x == z);
}

TEST(Polinom, can_mul_const)
{
	Polinom x("x+1");

	ASSERT_NO_THROW(x * 2);
}

TEST(Polinom, can_mul_const_2)
{
	Polinom x("x+1");
	Polinom z("2x+2");

	ASSERT_NO_THROW(x * 2 == z);
}

TEST(Polinom, can_mul_const_3)
{
	Polinom x("x+1");
	Polinom z("2x+2");

	x *= 2;

	ASSERT_NO_THROW(x == z);
}

TEST(Polinom, can_mul_polinom)
{
	Polinom x("x+1");
	Polinom y("y+1");

	ASSERT_NO_THROW(x*y);
}

TEST(Polinom, can_mul_polinom_2)
{
	Polinom x("x+1");
	Polinom y("y+1");
	Polinom z("xy+x+y+1");
	EXPECT_EQ(1, x*y == z);
}

TEST(Polinom, can_mul_polinom_3)
{
	Polinom x("x+1");
	Polinom y("y+1");
	Polinom z("xy+x+y+1");
	x *= y;
	EXPECT_EQ(1, x == z);
}

TEST(Polinom, can_calculating_the_value_at_a_point)
{
	point a(1, 2, 1);
	Polinom x("x+1");
	Polinom y("y+1");
	Polinom z = x * y;
	EXPECT_EQ(6, z[a]);
}

TEST(Polinom, can_calculating_the_value_at_a_point_2)
{
	point a(1, 2, 1);
	Polinom x("x+1");
	x *= 2;
	EXPECT_EQ(4, x[a]);
}