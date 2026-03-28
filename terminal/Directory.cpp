#include "Directory.h"
#include <iostream>
#include <algorithm>

Directory::Directory(const std::string& name, Directory* parent)
    : Entry(name), parent(parent) {}
Directory::~Directory() {}

void Directory::list() const {
    for (const auto& child : children) {
        if (!child->isHidden()) {
            std::cout << child->getName() << std::endl;
        }
    }
}
bool Directory::isDirectory() const {
    return true;
}
Directory* Directory::asDirectory() {
    return this;
}
Directory* Directory::getDirectory(const std::string& name) const {
    auto child = findChild(name);
    if (child && child->isDirectory()) {
        return child->asDirectory();
    }
    return nullptr;
}
bool Directory::addChild(std::shared_ptr<Entry> child) {
    if (findChild(child->getName())) return false;
    children.push_back(child);
    return true;
}
bool Directory::removeChild(const std::string& name) {
    auto it = std::find_if(children.begin(), children.end(),
        [&name](const std::shared_ptr<Entry>& e) { return e->getName() == name; });
    if (it != children.end()) {
        children.erase(it);
        return true;
    }
    return false;
}
std::shared_ptr<Entry> Directory::findChild(const std::string& name) const {
    auto it = std::find_if(children.begin(), children.end(),
        [&name](const std::shared_ptr<Entry>& e) { return e->getName() == name; });
    if (it != children.end()) return *it;
    return nullptr;
}
Directory* Directory::getParent() const {
    return parent;
}
void Directory::setParent(Directory* parent) {
    this->parent = parent;
}