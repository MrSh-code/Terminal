#include "PostponedFile.h"
#include "SingleLineFile.h"
#include "MultiLineFile.h"
#include <iostream>

PostponedFile::PostponedFile(const std::string& name) : Entry(name), actualFile(nullptr) {}
PostponedFile::~PostponedFile() {}

std::string PostponedFile::getName() const {
    return actualFile ? actualFile->getName() : Entry::getName();
}
void PostponedFile::setName(const std::string& newName) {
    if (actualFile) actualFile->setName(newName);
    else Entry::setName(newName);
}
bool PostponedFile::isHidden() const {
    return actualFile ? actualFile->isHidden() : Entry::isHidden();
}
void PostponedFile::setHidden(bool hidden) {
    if (actualFile) actualFile->setHidden(hidden);
    else Entry::setHidden(hidden);
}
void PostponedFile::printContent() const {
    if (actualFile) actualFile->printContent();
    else std::cout << "File not yet initialized." << std::endl;
}
void PostponedFile::edit() {
    if (actualFile) {
        actualFile->edit();
        return;
    }

    std::cout << "File " << getName() << " is new. Choose type: (1) Single-line, (2) Multi-line: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        std::cout << "Enter content: ";
        std::string content;
        std::getline(std::cin, content);
        realizeAsSingle(content);
        std::cout << "File created and content set." << std::endl;
    } else if (choice == 2) {
        std::cout << "Enter lines (end with empty line):" << std::endl;
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(std::cin, line) && !line.empty()) {
            lines.push_back(line);
        }
        realizeAsMulti(lines);
        std::cout << "File created and content set." << std::endl;
    } else {
        std::cout << "Invalid choice. File remains postponed." << std::endl;
    }
}
void PostponedFile::list() const {
    if (actualFile) actualFile->list();
    // else ничего не делаем
}
bool PostponedFile::isDirectory() const {
    return actualFile ? actualFile->isDirectory() : false;
}
Directory* PostponedFile::asDirectory() {
    return actualFile ? actualFile->asDirectory() : nullptr;
}
Directory* PostponedFile::getDirectory(const std::string& name) const {
    return actualFile ? actualFile->getDirectory(name) : nullptr;
}
void PostponedFile::realizeAsSingle(const std::string& content) {
    actualFile = std::make_shared<SingleLineFile>(getName(), content);
    actualFile->setHidden(isHidden());
}
void PostponedFile::realizeAsMulti(const std::vector<std::string>& lines) {
    actualFile = std::make_shared<MultiLineFile>(getName(), lines);
    actualFile->setHidden(isHidden());
}