#include "MultiLineFile.h"
#include <iostream>

MultiLineFile::MultiLineFile(const std::string& name, const std::vector<std::string>& lines)
    : Entry(name), lines(lines) {}

void MultiLineFile::printContent() const {
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
}
void MultiLineFile::edit() {
    std::cout << "Editing multi-line file " << getName() << ". Enter lines (end with empty line):" << std::endl;
    std::vector<std::string> newLines;
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        newLines.push_back(line);
    }
    lines = newLines;
    std::cout << "File updated." << std::endl;
}