// Neuro2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include "NeuroNetwork.h"

using namespace NeuralNet;

int main()
{
	NeuralImportData* Import = new NeuralImportData;
	Import->Patterns = new NeuralPattern[4];
	Import->ICount = 2;
	Import->OCount = 1;
	Import->PatternCount = 4;
	//-fillup
	Import->Patterns[0].Inputs = new double[2];
	Import->Patterns[0].Inputs[0] = 0.0;
	Import->Patterns[0].Inputs[1] = 0.0;
	Import->Patterns[0].Outputs = new double;
	Import->Patterns[0].Outputs[0] = 0.0;

	Import->Patterns[1].Inputs = new double[2];
	Import->Patterns[1].Inputs[0] = 1.0;
	Import->Patterns[1].Inputs[1] = 0.0;
	Import->Patterns[1].Outputs = new double;
	Import->Patterns[1].Outputs[0] = 1.0;

	Import->Patterns[2].Inputs = new double[2];
	Import->Patterns[2].Inputs[0] = 0.0;
	Import->Patterns[2].Inputs[1] = 1.0;
	Import->Patterns[2].Outputs = new double;
	Import->Patterns[2].Outputs[0] = 1.0;

	Import->Patterns[3].Inputs = new double[2];
	Import->Patterns[3].Inputs[0] = 1.0;
	Import->Patterns[3].Inputs[1] = 1.0;
	Import->Patterns[3].Outputs = new double;
	Import->Patterns[3].Outputs[0] = 0.0;
	//-
	NeuralNetwork* NeuralNet = new NeuralNetwork(Import, 3);

	system("Pause");
	return 0;
}

