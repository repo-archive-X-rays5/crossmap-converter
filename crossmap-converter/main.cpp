#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

std::string filename = "crossmap-in.txt";

int main(int argc, char* argv[]) {
	if (argc > 1) {
		filename = argv[1];
		std::cout << "file was given as arg\n";
	}
	if (std::filesystem::exists(filename)) {
		std::ifstream reader(filename);
		if (!reader.is_open()) {
			std::cout << "failed to open " << filename << " for reading\n";
			return EXIT_FAILURE;
		}
		
		std::vector<std::string> lines;
		std::string buffer;
		std::cout << "starting reading\n";
		while (std::getline(reader, buffer)) {
			std::cout << "reading line " << buffer << "\n";
			lines.emplace_back(buffer);
		}
		std::cout << "done reading\n";
		reader.close();
		
		try {
			for (int i = 0; i < lines.size(); i++) {
				if (lines[i].empty() || lines[i].find("//") != std::string::npos) {
					continue;
				}
				std::cout << i << ": " << lines[i] << " -> ";
				if (lines[i].at(0) != '{') {
					lines[i].insert(0, "{");
				}
				if (lines[i].at(lines[i].size() - 1) != '}') {
					lines[i].insert(lines[i].size() - 1, "}");
				}
				std::cout << lines[i] << "\n";
			}
		}
		catch (std::exception& e) {
			std::cout << "std exception " << e.what() << "\n";
		}
		catch (...) {
			std::cout << "unkown exception\n";
		}
		std::cout << "done converting\nprinting to file\n";

		std::ofstream writer("crossmap-out.txt");
		if (!writer.is_open()) {
			std::cout << "failed to open crossmap-out.txt for writing\n";
			return EXIT_FAILURE;
		}
		std::cout << lines.size() << "\n";
		for (auto&& line : lines) {
			std::cout << "writing " << line << "\n";
			writer << line << "\n";
		}
		writer.close();

		std::cout << "converted " << lines.size() << " lines\n";
		system("pause");
	}
	else {
		std::cout << filename << " not found\n";
	}
	return EXIT_SUCCESS;
}