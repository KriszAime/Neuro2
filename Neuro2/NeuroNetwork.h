#pragma once
#include <memory.h>
#include <immintrin.h>
#include <climits>

namespace NeuralNet {
	struct NeuralPattern
	{
		double* Inputs;
		double* Outputs;
	};
	struct NeuralImportData
	{
		NeuralPattern* Patterns;
		long ICount, OCount, PatternCount;
	};
	struct NeuralHiddenLayer
	{
		double* Hidden; //node count
		double** WeightIH; //Inputs Count * Hidden Count (Ez csak Layerenként más cím, Patternenként ugyanaz) *
		double* SumH; //weighted contribution from each input unit
		int NumHiddenNodes; //<-node count
	};
	struct NeuralMemory
	{
		double* Input;
		double* Output;
		double* Target;
		NeuralHiddenLayer* HiddenLayers;
		double** WeightHO; //Last Hidden Count * NumOutput *
	};
	class NeuralNetwork
	{
	public:
		NeuralNetwork(NeuralImportData* TrainingData, int HiddenCount);
		NeuralNetwork(NeuralImportData* TrainingData, int HiddenCount, double eta, double alpha, double smallwt);


		bool AddHiddenLayer(int NumberOfNeurons);
		bool TrainUntil(double AcceptedError, unsigned long MaxEpochs, bool IsComment); //Little number ex: 0.0004, Big Number ex: 99000
		//bool Test
	private:
		double hwrandom32();
		NeuralMemory *Memory = nullptr; //Count = PatternCount
		int PatternCount, NumInput, NumOutput, NumHiddenLayers = 1;
		int* ranpat=nullptr; //Pattern Futtatás sorrend
		double eta = 0.5, alpha = 0.9, smallwt = 0.5;
	};

}
