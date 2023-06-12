#include "FiniteAutomata.h"
#include<iostream>
#include <fstream>
class AutomatonFileHandler {
public:
	FiniteAutomata readFromFile(const char* fileName);
	void writeToFile(const char* fileName,const FiniteAutomata& automaton);
};
void AutomatonFileHandler::writeToFile(const char* fileName, const FiniteAutomata& automaton) {
	std::ofstream output(fileName,std::ios::out|std::ios::binary);
	if (!output.is_open())
	{
		throw std::invalid_argument("Invalid path");
	}
	//Nodes
	output.write((char*)&automaton.nodes,4);
	//StartNode
	output.write((const char*)&automaton.startNode,sizeof(int));
	//FinalStates
	output.write((const char*)&automaton.finalStates.size, sizeof(int));
	output.write((const char*)&automaton.finalStates.capacity, sizeof(int));
	output.write((const char*)automaton.finalStates.data, automaton.finalStates.getBucketsCount() * sizeof(char));
	//Alphabet
	output.write((const char*)&automaton.alphabet.size, sizeof(int));
	output.write((const char*)&automaton.alphabet.capacity, sizeof(int));
	output.write((const char*)automaton.alphabet.elements, automaton.alphabet.getSize()*sizeof(char));
	//Transitions
	output.write((const char*)&automaton.automata.size,sizeof(int));
	output.write((const char*)&automaton.automata.capacity, sizeof(int));
	for (int i = 0; i < automaton.automata.getSize(); i++)
	{
		output.write((const char*)&automaton.automata[i].size,sizeof(int));
		for (int j = 0; j < automaton.automata[i].getSize(); j++)
		{
			output.write((const char*)&automaton.automata[i][j].dest,sizeof(int));
			output.write((const char*)&automaton.automata[i][j].symbol,sizeof(char));
		}

	}
	output.close();
}
FiniteAutomata AutomatonFileHandler::readFromFile(const char* fileName) {
	std::ifstream input(fileName,std::ios::binary);
	if (!input.is_open())
	{
		throw std::invalid_argument("Invalid path");
	}

	FiniteAutomata result;
	//Nodes
	input.read((char*)&result.nodes,sizeof(int));
	//StartNode
	input.read((char*)&result.startNode, sizeof(int));
	//FinalStates
	int finalStatesSize = 0;
	int finalStatesCapacity = 0;
	input.read((char*)&finalStatesSize, sizeof(int));
	input.read((char*)&finalStatesCapacity, sizeof(int));
	BitSet finals(finalStatesSize);
	input.read((char*)finals.data, ((finalStatesCapacity + 1) / 8 + 1)* sizeof(char));
	result.finalStates = std::move(finals);
	//Alphabet
	int alphabetSize = 0;
	int alphabetCapacity = 0;
	input.read((char*)&alphabetSize, sizeof(int));
	input.read((char*)&alphabetCapacity, sizeof(int));
	CustomCollection<char>alphabet(alphabetCapacity);
	input.read((char*)alphabet.elements, alphabetSize * sizeof(char));
	alphabet.size = alphabetSize;
	result.alphabet = std::move(alphabet);
	//Transitions
	int automatonCapacity = 0;
	int automatonSize = 0;
	input.read((char*)&automatonSize, sizeof(int));
	input.read((char*)&automatonCapacity, sizeof(int));
	CustomCollection<CustomCollection<Transition>>automata(automatonCapacity);
	automata.size = automatonSize;
	for (int i = 0; i < automatonSize; i++)
	{
		int transitionsCount = 0;
		input.read((char*)&transitionsCount, sizeof(int));
		for (int j = 0; j < transitionsCount; j++)
		{
			int dest = 0;
			char symbol = 0;
			input.read((char*)&dest, sizeof(int));
			input.read((char*)&symbol, sizeof(char));
			automata[i].add(Transition(dest,symbol));
		}
	}
	result.automata = std::move(automata);
	input.close();

	return result;
}
