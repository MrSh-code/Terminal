#include "SingleLineFile.h"
#include <iostream>

SingleLineFile::SingleLineFile(const std::string& name, const std::string& content)
    : Entry(name), content(content) {}

void SingleLineFile::printContent() const {
    std::cout << content << std::endl;
}
void SingleLineFile::edit() {
    std::cout << "Enter new content for " << getName() << ": ";
    std::getline(std::cin, content);
    std::cout << "File updated." << std::endl;
}