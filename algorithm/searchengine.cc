#include <iostream>
#include <unordered_map>

std

class SearchEngine {
public:
	SearchEngine(std::) {}
};


int main() {
	auto corpus = extract_copus();
	SearchEngine e(corpus);
	std::string query;
	while (true) {
		std::cin >> query;
		if (query == "exit") {
			std::cout << "Goodbye!\n";
			break;
		}
		auto result = e.search(query, 5);
		if (result.size() == 0) {
			std::cout << "There are no results for that query. :(";
		}
		else {
			std::cout << "Top results: \n";

		}
	}
}