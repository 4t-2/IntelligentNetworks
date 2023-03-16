#include "../../../IntNet/intnet.hpp"

#include <fstream>
#include <iostream>

inline float ranfloat(float f1, float f2)
{
	return (((float)std::rand() / (float)RAND_MAX) * (std::abs(f1) + std::abs(f2))) - std::abs(f1);
}

void XORexample()
{
	in::NetworkStructure netStruct(9, 5, 2, 1,
							   {
								   {0, 5, ranfloat(-1, 1)}, //
								   {1, 6, ranfloat(-1, 1)}, //
								   {2, 7, ranfloat(-1, 1)}, //
								   {3, 5, ranfloat(-1, 1)}, //
								   {3, 6, ranfloat(-1, 1)}, //
								   {4, 5, ranfloat(-1, 1)}, //
								   {4, 6, ranfloat(-1, 1)}, //
								   {5, 7, ranfloat(-1, 1)}, //
								   {6, 7, ranfloat(-1, 1)}, //
							   });

	std::cout << netStruct << '\n';

	in::NeuralNetwork network(netStruct);

	network.setInputNode(0, 1);
	network.setInputNode(1, 1);
	network.setInputNode(2, 1);

	std::fstream fs("plot.txt", std::ios::out);

	for (int i = 0; i < 10000; i++)
	{
		network.setInputNode(3, 0);
		network.setInputNode(4, 0);
		network.update();
		fs << i << " " << network.backpropagation({0}) << '\n';

		network.setInputNode(3, 0);
		network.setInputNode(4, 1);
		network.update();
		fs << i << " " << network.backpropagation({1}) << '\n';

		network.setInputNode(3, 1);
		network.setInputNode(4, 0);
		network.update();
		fs << i << " " << network.backpropagation({1}) << '\n';

		network.setInputNode(3, 1);
		network.setInputNode(4, 1);
		network.update();
		fs << i << " " << network.backpropagation({0}) << '\n';
	}

	network.setInputNode(3, 0);
	network.setInputNode(4, 0);
	network.update();
	std::cout << network.getNode(7).value << '\n';

	network.setInputNode(3, 0);
	network.setInputNode(4, 1);
	network.update();
	std::cout << network.getNode(7).value << '\n';

	network.setInputNode(3, 1);
	network.setInputNode(4, 0);
	network.update();
	std::cout << network.getNode(7).value << '\n';

	network.setInputNode(3, 1);
	network.setInputNode(4, 1);
	network.update();
	std::cout << network.getNode(7).value << '\n';

	fs.close();

	network.destroy();
}

void XORexample2()
{
	in::NetworkStructure netStruct(3, {10, 10, 10}, 1);

	in::NetworkStructure::randomWeights(netStruct);

	std::cout << netStruct << '\n';

	in::NeuralNetwork network(netStruct);

	network.setInputNode(0, 1);

	std::fstream fs("plot.txt", std::ios::out);

	for (int i = 0; i < 10000; i++)
	{
		network.setInputNode(1, 0);
		network.setInputNode(2, 0);
		network.update();
		fs << i << " " << network.backpropagation({0}) << '\n';

		network.setInputNode(1, 0);
		network.setInputNode(2, 1);
		network.update();
		fs << i << " " << network.backpropagation({1}) << '\n';

		network.setInputNode(1, 1);
		network.setInputNode(2, 0);
		network.update();
		fs << i << " " << network.backpropagation({1}) << '\n';

		network.setInputNode(1, 1);
		network.setInputNode(2, 1);
		network.update();
		fs << i << " " << network.backpropagation({0}) << '\n';
	}

	network.setInputNode(1, 0);
	network.setInputNode(2, 0);
	network.update();
	std::cout << network.getNode(network.getTotalNodes()-1).value << '\n';

	network.setInputNode(1, 0);
	network.setInputNode(2, 1);
	network.update();
	std::cout << network.getNode(network.getTotalNodes()-1).value << '\n';

	network.setInputNode(1, 1);
	network.setInputNode(2, 0);
	network.update();
	std::cout << network.getNode(network.getTotalNodes()-1).value << '\n';

	network.setInputNode(1, 1);
	network.setInputNode(2, 1);
	network.update();
	std::cout << network.getNode(network.getTotalNodes()-1).value << '\n';

	fs.close();

	network.destroy();
}

int main()
{
	std::srand(time(NULL));

	// XORexample();
	XORexample2();
}