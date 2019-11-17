#pragma once

namespace NeuralNet {
	struct NeuralPattern
	{
		double* Inputs;
		double* Outputs;
	};
	struct NeuralImportData
	{
		NeuralPattern* Patterns;
		unsigned long PatternICount, PatternOCount, PatternCount;
	};
	struct NeuralHiddenLayer
	{
		double* Hidden; //node count
		double** WeightIH; //Inputs Count * node Count
		double* SumH; //weighted contribution from each input unit
		int NumHidden; //<-node count
	};
	struct NeuralMemory
	{
		double* Input;
		double* Output;
		NeuralHiddenLayer* Layers;
	};
	class NeuralNetwork
	{
	public:
		NeuralNetwork(NeuralImportData *TrainingData)
		{
			PatternCount = TrainingData->PatternCount;
			NumInput = TrainingData->PatternICount;
			NumOutput = TrainingData->PatternOCount;
		}

		bool AddHiddenLayer(int NumberOfNeurons);
		bool TrainUntil(double AcceptedError, unsigned long MaxEpochs, bool IsComment); //Little number ex: 0.0004, Big Number ex: 99000
		//bool Test
	private:
		NeuralMemory *Memory = nullptr; //Count = PatternCount
		int PatternCount, NumInput, NumOutput;
		int* ranpat=nullptr; //Pattern Futtatás sorrend
	};

}
