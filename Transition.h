#pragma once
struct Transition {
	int dest = -1;
	char symbol = '\0';
	Transition() = default;
	Transition(int dest, char symbol);
};