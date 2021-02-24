#include "utpolynomial.h"

#include <gtest.h>


TEST(Monomial, can_create_monomial) {
	Monomial mon(1, 123);
	ASSERT_EQ(mon.coeff, 1);
}

TEST(Monomial, x_power_calculated_correctly) {
	Monomial mon(1, 123);
	ASSERT_EQ(mon.xPower(), 1);
}

TEST(Monomial, y_power_calculated_correctly) {
	Monomial mon(1, 123);
	ASSERT_EQ(mon.yPower(), 2);
}

TEST(Monomial, z_power_calculated_correctly) {
	Monomial mon(1, 123);
	ASSERT_EQ(mon.zPower(), 3);
}

TEST(Monomial, can_add_monomials) {
	Monomial mon1(3, 1);
	Monomial mon2(4, 1);
	ASSERT_EQ((mon1 + mon2).coeff, 7);
}

TEST(Monomial, can_multiply_monomials) {
	Monomial mon1(3, 1);
	Monomial mon2(4, 1);
	Monomial expRes(12, 2);
	ASSERT_EQ(mon1 * mon2, expRes);
}

TEST(Polynomial, polynomial_empty_upon_creation) {
	Polynomial pol;
	ASSERT_TRUE(pol.empty());
}

TEST(Polynomial, can_add_empty_polynomials) {
	Polynomial pol1, pol2;
	ASSERT_TRUE((pol1 + pol2).empty());
}

TEST(Polynomial, can_add_polynomials_when_second_is_empty) {
	Polynomial pol1, pol2;
	Monomial mon(1, 123);
	pol1.insert_after(mon, nullptr);
	ASSERT_EQ(pol1 + pol2, pol1);
}

TEST(Polynomial, can_add_polynomials_when_first_is_empty) {
	Polynomial pol1, pol2;
	Monomial mon(1, 123);
	pol2.insert_after(mon, nullptr);
	ASSERT_EQ(pol1 + pol2, pol2);
}

TEST(Polynomial, can_add_polynomials_when_they_have_no_powers_in_common) {
	Polynomial pol1, pol2, expRes;
	Monomial mon1(1, 123), mon2(1, 234), mon3(2, 345);
	pol1.insert_after(mon1, nullptr);
	Node<Monomial>* current = nullptr;
	current = pol2.insert_after(mon2, current);
	pol2.insert_after(mon3, current);
	current = nullptr;
	current = expRes.insert_after(mon1, current);
	current = expRes.insert_after(mon2, current);
	current = expRes.insert_after(mon3, current);
	ASSERT_EQ(pol1 + pol2, expRes);
}

TEST(Polynomial, can_add_polynomials_when_they_have_powers_in_common) {
	Polynomial pol1, pol2, expRes;
	Monomial mon1(1, 234), mon2(1, 234), mon3(2, 345), mon4(2, 234);
	pol1.insert_after(mon1, nullptr);
	Node<Monomial>* current = nullptr;
	current = pol2.insert_after(mon2, current);
	pol2.insert_after(mon3, current);
	current = nullptr;
	current = expRes.insert_after(mon4, current);
	current = expRes.insert_after(mon3, current);
	ASSERT_EQ(pol1 + pol2, expRes);
}


TEST(Polynomial, can_multiply_empty_polynomials) {
	Polynomial pol1, pol2;
	ASSERT_TRUE((pol1 * pol2).empty());
}

TEST(Polynomial, can_multiply_polynomials_when_second_is_empty) {
	Polynomial pol1, pol2;
	Monomial mon(1, 123);
	pol1.insert_after(mon, nullptr);
	ASSERT_EQ(pol1 * pol2, pol2);
}

TEST(Polynomial, can_multiply_polynomials_when_first_is_empty) {
	Polynomial pol1, pol2;
	Monomial mon(1, 123);
	pol2.insert_after(mon, nullptr);
	ASSERT_EQ(pol1 * pol2, pol1);
}

TEST(Polynomial, can_multiply_polynomials) {
	Polynomial pol1, pol2, expRes;
	Monomial mon1(1, 123), mon2(1, 234), mon3(2, 345), mon4(3, 234), mon5(6, 357), mon6(2, 468), mon7(2, 579);
	Node<Monomial>* current = nullptr;
	current = pol1.insert_after(mon1, current);
	pol1.insert_after(mon2, current);
	current = nullptr;
	current = pol2.insert_after(mon3, current);
	pol2.insert_after(mon4, current);
	current = nullptr;
	current = expRes.insert_after(mon5, current);
	current = expRes.insert_after(mon6, current);
	current = expRes.insert_after(mon7, current);
	ASSERT_EQ(pol1 * pol2, expRes);
}