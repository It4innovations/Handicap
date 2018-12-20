#include <iostream>
#include <vector>
#include "GraphLabelings/GraphLabeling.h"
#include "Graphs/Factories/ExtendedHandicapGraphFactory.h"
#include "Outputs/GraphInfoPrinter.h"
#include "Solvers/kSumProblemSolver.h"
#include "Concurrency/ThreadSafeQueue.h"
#include "Concurrency/ThreadPool.h"
#include <thread>
#include <mutex>

constexpr int REGULAR_NUMBER = 5;
constexpr int THREAD_COUNT = 4;
constexpr int VERTICES_COUNT = 12;
constexpr int STARTING_LABEL = 1;

int GraphLabeling::numberOfSolution = 0;
// This program search extended handicap magic labeling
int main() {

	std::cout.sync_with_stdio(false);
	std::cout.tie();

	if (REGULAR_NUMBER > 5 || REGULAR_NUMBER < 2) {
		std::cerr << "Regular number must be in <2;4>\n. It is equal to " << REGULAR_NUMBER << '\n';
		return 1;
	}


	if (THREAD_COUNT < 1) {
		std::cerr << "CONST THREAD_COUT must be greater than 0. Please change them.\n";
		return 1;
	}

	std::unique_ptr<ExtendedHandicapGraphFactory> handicapGraphFactory(new ExtendedHandicapGraphFactory());
	std::shared_ptr<ExtendedHandicapGraph> graph;

	int vertexCount = VERTICES_COUNT;
	//std::cin >> vertexCount;

	try {
		// Create extended handicap graphs
		graph = handicapGraphFactory->create(vertexCount, REGULAR_NUMBER);
	} catch (const char * msg) {
		std::cerr << msg;
		return 1;
	}
	GraphInfoPrinter printer;
	printer.print(graph);

	if (STARTING_LABEL < 1 || STARTING_LABEL > graph->getVerticesCount() + 1 || STARTING_LABEL == graph->getMissingLabel()) {
		std::cerr << "CONST STARTING_LABEL is not any label in labeling.\nPlease select another STARTING LABEL.\n";
		return 1;
	}

	std::unique_ptr<int[]> arr(new int[vertexCount - 1]());
	int index = 0;
	for (int i = 1; i < graph->getVerticesCount() + 2; i++) {
		if (i == STARTING_LABEL || i == graph->getMissingLabel()) continue;
		arr[index] = i;
		++index;
	}

	//number of threads running parallel
	ThreadPool pool(THREAD_COUNT);
	std::stack<int> stack;
	kSumProblemSolver<int> solver;
	solver.setK(REGULAR_NUMBER);
	solver.setSearchNumber(STARTING_LABEL + graph->getMagicConstant());
	solver.solve(arr, index, stack);
	const auto countOfResult = (int) (stack.size() / REGULAR_NUMBER);
	std::mutex mut;

	for (int i = 0; i < countOfResult; ++i) {
		std::vector<int> vec;
		for (int j = 0; j < REGULAR_NUMBER; ++j) {
			vec.push_back(stack.top());
			stack.pop();
		}
		int startingLabel = STARTING_LABEL;
		pool.addJob([&graph, startingLabel, vec, &mut]() {
			std::unique_ptr<GraphLabeling> graphLabeling(new GraphLabeling(graph));
			graphLabeling->prepareSolve(startingLabel, vec, mut);
		});
	}
	pool.execute();

	std::cout << "END\n";
	return 0;
}

