#include "Entry.h"
#include <iostream>

Entry::Entry(const std::string& name) : name(name), hidden(false) {}
Entry::~Entry() {}

std::string Entry::getName() const { return name; }
void Entry::setName(const std::string& newName) { name = newName; }
bool Entry::isHidden() const { return hidden; }
void Entry::setHidden(bool hidden) { this->hidden = hidden; }

void Entry::printContent() const {
    std::cout << "Cannot print content: not a file." << std::endl;
}
void Entry::edit() {
    std::cout << "Cannot edit: not a file." << std::endl;
}
void Entry::list() const {
    // ничего не делаем для не-директорий
}
bool Entry::isDirectory() const {
    return false;
}
Directory* Entry::asDirectory() {
    return nullptr;
}
Directory* Entry::getDirectory(const std::string& name) const {
    return nullptr;
}