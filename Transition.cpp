#pragma once
#include "Transition.h"

Transition::Transition(int dest, char symbol) {
	this->dest = dest;
	this->symbol = symbol;
}