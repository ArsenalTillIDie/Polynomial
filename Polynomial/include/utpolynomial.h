
#include <iostream>
#include "utlist.h"

const int maxPower = 10;

class Polynomial;

class Monomial {
public:
	int power;
	int coeff;
	Monomial(int cf = 0, int p = -1);
	Monomial(const Monomial& mon);
	int xPower() const;
	int yPower() const;
	int zPower() const;
	bool monomialWithinBounds();
	Monomial operator+(Monomial mon);
	Monomial operator*(Monomial mon);
	Polynomial operator*(Polynomial pol);
	bool operator==(const Monomial mon) const;
	friend std::ostream& operator<<(std::ostream& os, const Monomial& mon);
};

class Polynomial : public List<Monomial> {
public:
	Polynomial();
	Polynomial(const Polynomial& pol);
	Polynomial operator+(const Polynomial& pol);
	Polynomial operator*(Polynomial pol);
	Polynomial operator*(Monomial mon);
	bool operator==(const Polynomial lst) const;
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& pol);
};

Monomial::Monomial(int cf, int p){
	coeff = cf;
	power = p;
	if (!monomialWithinBounds()) throw "Monomial overflow detected";
}
Monomial::Monomial(const Monomial& mon) {
	power = mon.power;
	coeff = mon.coeff;
}
int Monomial::xPower() const {
	return power / (maxPower * maxPower);
}
int Monomial::yPower() const {
	return (power / maxPower) % maxPower;
}
int Monomial::zPower() const {
	return power % maxPower;
}
bool Monomial::monomialWithinBounds(){
	if((xPower() < maxPower) && (yPower() < maxPower) && (zPower() < maxPower)) return true;
	else return false;
}
Monomial Monomial::operator+(Monomial mon) {
	if (power != mon.power)
		throw "Monomials' powers don't match";
	else {
		Monomial newMon(coeff + mon.coeff, power);
		return newMon;
	}
}
Monomial Monomial::operator*(Monomial mon) {
	Monomial newMon;
	newMon.coeff = coeff * mon.coeff;
	newMon.power = power + mon.power;
	if (!monomialWithinBounds()) throw "Monomial overflow detected";
	return newMon;
}
Polynomial Monomial::operator*(Polynomial pol) {
	Polynomial newPol; 
	Node<Monomial>* current = nullptr;
	for (Polynomial::iterator it = pol.begin(); it != pol.end(); ++it) {
		current = newPol.insert_after(*this * it->data, current);
	}
	return newPol;
}
bool Monomial::operator==(const Monomial mon) const{
	if (power == mon.power && coeff == mon.coeff) return true;
	else return false;
}

std::ostream& operator<<(std::ostream& os, const Monomial& mon)
{
	os << mon.coeff << "*";
	if (mon.xPower() != 0) os << "x^" << mon.xPower();
	if (mon.yPower() != 0) os << "y^" << mon.yPower();
	if (mon.zPower() != 0) os << "z^" << mon.zPower();
	return os;
}


Polynomial::Polynomial() : List<Monomial>() {
}
Polynomial::Polynomial(const Polynomial& pol) : List<Monomial>() {
}
Polynomial Polynomial::operator+(const Polynomial& pol) {
	Polynomial newPol;
	Polynomial::iterator it1 = begin();
	Polynomial::iterator it2 = pol.begin();
	Node<Monomial>* current = nullptr;
	while (it1 != end() && it2 != pol.end()) {
		if (it1->data.power < it2->data.power) {
			current = newPol.insert_after(it1->data, current);
			++it1;
		}
		else if (it1->data.power == it2->data.power) {
			if((it1->data + it2->data).coeff != 0) current = newPol.insert_after(it1->data + it2->data, current);
			++it1;
			++it2;
		}
		else if (it1->data.power > it2->data.power) {
			current = newPol.insert_after(it2->data, current);
			++it2;
		}
	}
	if (it1 == end()) {
		for (; it2 != pol.end(); ++it2)
			current = newPol.insert_after(it2->data, current);
	}
	if (it2 == pol.end()) {
		for (; it1 != end(); ++it1)
			current = newPol.insert_after(it1->data, current);
	}
	return newPol;
}
Polynomial Polynomial::operator*(Polynomial pol) {
	Polynomial newPol;
	for (Polynomial::iterator it = pol.begin(); it != pol.end(); ++it) {
		newPol = newPol + it->data * *this;
	}
	return newPol;
}
Polynomial Polynomial::operator*(Monomial mon) {
	Polynomial newPol;
	Node<Monomial>* current = nullptr;
	for (Polynomial::iterator it = begin(); it != end(); ++it) {
		current = newPol.insert_after(mon * it->data, current);
	}
	return newPol;
}
bool Polynomial::operator==(const Polynomial lst) const {
	Polynomial::iterator it1 = begin();
	Polynomial::iterator it2 = lst.begin();
	while (true) {
		if (it1 == end()) {
			if (it2 != end())
				return false;
			else return true;
		}
		if (it2 == end()) {
			if (it1 != end())
				return false;
			else return true;
		}
		if (!(it1->data == it2->data)) return false;
		++it1;
		++it2;
	}
}
std::ostream& operator<<(std::ostream& os, const Polynomial& pol)
{
	for (Polynomial::iterator it = pol.begin(); it != pol.end(); ++it) {
		os << "+" << it->data;
	}
	return os;
}

