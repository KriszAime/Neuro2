#include "NeuroNetwork.h"
#include <memory.h>

NeuralNet::NeuralNetwork::NeuralNetwork(NeuralImportData* TrainingData, int HiddenCount)
{
	Memory = new NeuralMemory[TrainingData->PatternCount];
	//- Output Weights
	Memory->WeightHO = new double* [TrainingData->OCount];
	for (int i = 0; i < TrainingData->OCount; i++)
		Memory->WeightHO[i] = new double[HiddenCount];
	//-
	ranpat = new int[TrainingData->PatternCount];
	//-Creating 1 Hidden layer
	(*Memory).HiddenLayers = new NeuralHiddenLayer;
	(*Memory).HiddenLayers->WeightIH = new double* [HiddenCount];
	for (int i = 0; i < HiddenCount; i++)
		(*Memory).HiddenLayers->WeightIH[i] = new double[TrainingData->ICount];
	//-
	for (int i = 0; i < TrainingData->PatternCount; ranpat[i++] = i)
	{
		Memory[i].Input = new double[TrainingData->ICount];
		Memory[i].Target = new double[TrainingData->OCount];
		memcpy(Memory[i].Input, TrainingData->Patterns[i].Inputs, sizeof(double) * TrainingData->ICount);
		memcpy(Memory[i].Target, TrainingData->Patterns[i].Outputs, sizeof(double) * TrainingData->OCount);
		Memory[i].Output = new double[TrainingData->OCount];
		Memory[i].WeightHO = Memory->WeightHO; //Mind Ugyanarra a Layerre mutat.
		//-Creating 1 Hidden layer
		if (i > 0)Memory[i].HiddenLayers = new NeuralHiddenLayer;
		Memory[i].HiddenLayers->WeightIH = (*Memory).HiddenLayers->WeightIH; //Mind Ugyanarra a Layerre mutat.
		Memory[i].HiddenLayers->Hidden = new double[HiddenCount];
		Memory[i].HiddenLayers->SumH = new double[TrainingData->ICount];
		Memory[i].HiddenLayers->NumHiddenNodes = HiddenCount;
		//-
	}
	PatternCount = TrainingData->PatternCount;
	NumInput = TrainingData->ICount;
	NumOutput = TrainingData->OCount;
}

NeuralNet::NeuralNetwork::NeuralNetwork(NeuralImportData* TrainingData, int HiddenCount, double eta, double alpha, double smallwt) : NeuralNetwork(TrainingData, HiddenCount) //ezt tesztelni?
{
	this->eta = eta;
	this->alpha = alpha;
	this->smallwt = smallwt;
}

bool NeuralNet::NeuralNetwork::AddHiddenLayer(int NumberOfNeurons)
{

	return false;
}

bool NeuralNet::NeuralNetwork::TrainUntil(double AcceptedError, unsigned long MaxEpochs, bool IsComment)
{

	return false;
}
