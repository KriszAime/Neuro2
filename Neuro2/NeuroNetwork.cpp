#include "NeuroNetwork.h"
#include <iostream>

NeuralNet::NeuralNetwork::NeuralNetwork(NeuralImportData* TrainingData, int HiddenCount)
{
	Memory = new NeuralMemory[TrainingData->PatternCount];
	//- Output Weights
	Memory->WeightHO = new double* [HiddenCount];
	for (int i = 0; i < HiddenCount; i++)
		Memory->WeightHO[i] = new double[TrainingData->OCount];
	//-
	ranpat = new int[TrainingData->PatternCount];
	//-Creating 1 Hidden layer
	(*Memory).HiddenLayers = new NeuralHiddenLayer;
	(*Memory).HiddenLayers->WeightIH = new double* [TrainingData->ICount];
	for (int i = 0; i < TrainingData->ICount; i++)
		(*Memory).HiddenLayers->WeightIH[i] = new double[HiddenCount];
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
	NumHiddenLayers = 1;
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
	/* initialize WeightIH and DeltaWeightIH */
	double** DeltaWeightIH = new double* [NumInput];
	for (int i = 0; i < NumInput; i++)
	{
		DeltaWeightIH[i] = new double[Memory->HiddenLayers->NumHiddenNodes];
		for (int h = 0; h < Memory->HiddenLayers->NumHiddenNodes; h++)
		{
			DeltaWeightIH[i][h] = 0.0;
			Memory->HiddenLayers->WeightIH[i][h] = 2.0 * (hwrandom32() - 0.5) * smallwt;
		}
	}
	/* initialize WeightHH and DeltaWeightHH */
	double*** DeltaWeightLIH = new double** [NumHiddenLayers];
	if (NumHiddenLayers > 1)
	{
		for (int l = 1; l < NumHiddenLayers; l++)
		{
			DeltaWeightLIH[l] = new double* [Memory->HiddenLayers[l - 1].NumHiddenNodes];
			for (int ih = 0; ih < Memory->HiddenLayers[l - 1].NumHiddenNodes; ih++)
			{
				DeltaWeightLIH[l][ih] = new double[Memory->HiddenLayers[l].NumHiddenNodes];
				for (int hh = 0; hh < Memory->HiddenLayers[l].NumHiddenNodes; hh++)
				{
					DeltaWeightLIH[l][ih][hh] = 0.0;
					Memory->HiddenLayers[l].WeightIH[ih][hh] = 2.0 * (hwrandom32() - 0.5) * smallwt;
				}
			}

		}
	}

	/* initialize WeightHO and DeltaWeightHO */
	double** DeltaWeightHO = new double* [Memory->HiddenLayers[NumHiddenLayers - 1].NumHiddenNodes];
	for (int h = 0; h < Memory->HiddenLayers[NumHiddenLayers - 1].NumHiddenNodes; h++)
	{
		DeltaWeightHO[h] = new double[NumOutput];
		for (int o = 0; o < NumOutput; o++)
		{
			DeltaWeightHO[h][o] = 0.0;
			Memory->WeightHO[h][o] = 2.0 * (hwrandom32() - 0.5) * smallwt;
		}
	}

	for (size_t p = 0; p < PatternCount; p++)
		ranpat[p] = p;

	double Error;
	for (size_t epoch = 0; epoch < MaxEpochs; epoch++)
	{
		for (size_t p = 0; p < PatternCount; p++) /* randomize order of individuals */
		{
			int rp = hwrandom32_t(0, PatternCount-1);
			int tmp = ranpat[p]; ranpat[p] = ranpat[rp]; ranpat[rp] = tmp;
		}
		Error = 0.0; //set no error.
		for (size_t np = 0; np < PatternCount; np++) /* repeat for all the training patterns */
		{

		}
	}

	delete[] DeltaWeightIH, DeltaWeightLIH, DeltaWeightHO;
	return false;
}

double NeuralNet::NeuralNetwork::hwrandom32() //0..1
{
	unsigned int ret;
	_rdrand32_step(&ret);
	return ((double)ret / ((double)UINT_MAX + 1));
}

size_t NeuralNet::NeuralNetwork::hwrandom32_t(size_t from, size_t to) //int from...to - exclusive
{
	size_t ret;
	_rdrand32_step(&ret);
	return from + ret % ((to+1)-from);
}
