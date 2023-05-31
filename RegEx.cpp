#include "RegEx.h"
#include "Union.h"
#include "KleeneStar.h"
#include "Concatenation.h"
#include "Symbol.h"
bool RegEx::isEpsilon()const {
	return false;
}
RegEx* RegEx::getUnion(RegEx* right) {
	if (right==nullptr)
	{
		return this;
	}
	if (this==nullptr)
	{
		return right;
	}
	if (getString()==right->getString())
	{
		delete right;
		return this;
	}
	return new UnionRegEx(this,right);
}
RegEx* RegEx::getConcatenation(RegEx* right) {
	if (right==nullptr||this==nullptr)
	{
		return nullptr;
	}
	if (isEpsilon())
	{
		return right;
	}
	if (right->isEpsilon())
	{
		return this;
	}
	return new ConcatenationRegEx(this,right);
}
RegEx* RegEx::getKleeneStar() {
	if (this == nullptr)
	{
		return new Symbol('$');
	}
	if (isEpsilon())
	{
		return this;
	}
	return new KleeneStarRegEx(this);
}