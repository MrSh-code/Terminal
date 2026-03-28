#include "Terminal.h"
#include "PostponedFile.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

Terminal::Terminal() {
    root = std::make_shared<Directory>("/", nullptr);
    currentDir = root.get();
}

void Terminal::run() {
    std::string line;
    while (true) {
        std::cout << currentDir->getName() << "> ";
        std::getline(std::cin, line);
        if (line.empty()) continue;
        processCommand(line);
    }
}

void Terminal::processCommand(const std::string& line) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "help") {
        help();
    } else if (cmd == "exit") {
        exit();
    } else if (cmd == "ls") {
        ls();
    } else if (cmd == "cd") {
        std::string arg;
        iss >> arg;
        cd(arg);
    } else if (cmd == "cat") {
        std::string arg;
        iss >> arg;
        cat(arg);
    } else if (cmd == "touch") {
        std::string arg;
        iss >> arg;
        touch(arg);
    } else if (cmd == "mkdir") {
        std::string arg;
        iss >> arg;
        mkdir(arg);
    } else if (cmd == "rm") {
        std::string arg;
        iss >> arg;
        rm(arg);
    } else if (cmd == "restore") {
        std::string arg;
        iss >> arg;
        restore(arg);
    } else if (cmd == "mv") {
        std::string oldName, newName;
        iss >> oldName >> newName;
        mv(oldName, newName);
    } else if (cmd == "edit") {
        std::string arg;
        iss >> arg;
        edit(arg);
    } else {
        std::cout << "Unknown command. Type 'help' for list." << std::endl;
    }
}

void Terminal::help() const {
    std::cout << "Available commands:" << std::endl;
    std::cout << "help - show this help" << std::endl;
    std::cout << "exit - exit terminal" << std::endl;
    std::cout << "ls - list directory contents" << std::endl;
    std::cout << "cd <dir> - change directory" << std::endl;
    std::cout << "cat <file> - display file content" << std::endl;
    std::cout << "touch <file> - create a new file" << std::endl;
    std::cout << "mkdir <dir> - create a new directory" << std::endl;
    std::cout << "rm <name> - hide file/directory" << std::endl;
    std::cout << "restore <name> - restore hidden file/directory" << std::endl;
    std::cout << "mv <old> <new> - rename file/directory" << std::endl;
    std::cout << "edit <file> - edit file content" << std::endl;
}

void Terminal::exit() {
    std::cout << "Goodbye!" << std::endl;
    std::exit(0);
}

void Terminal::ls() const {
    currentDir->list();
}

void Terminal::cd(const std::string& path) {
    if (path == "..") {
        if (currentDir->getParent() != nullptr) {
            currentDir = currentDir->getParent();
        } else {
            std::cout << "Already at root." << std::endl;
        }
    } else if (path == ".") {
        // nothing
    } else {
        Directory* target = currentDir->getDirectory(path);
        if (target) {
            currentDir = target;
        } else {
            std::cout << "cd: no such directory: " << path << std::endl;
        }
    }
}

void Terminal::cat(const std::string& filename) {
    auto entry = currentDir->findChild(filename);
    if (entry) {
        entry->printContent();
    } else {
        std::cout << "cat: " << filename << ": No such file" << std::endl;
    }
}

void Terminal::touch(const std::string& filename) {
    if (currentDir->findChild(filename)) {
        std::cout << "touch: " << filename << " already exists" << std::endl;
        return;
    }
    auto newFile = std::make_shared<PostponedFile>(filename);
    currentDir->addChild(newFile);
    std::cout << "Created postponed file: " << filename << std::endl;
}

void Terminal::mkdir(const std::string& dirname) {
    if (currentDir->findChild(dirname)) {
        std::cout << "mkdir: " << dirname << " already exists" << std::endl;
        return;
    }
    auto newDir = std::make_shared<Directory>(dirname, currentDir);
    currentDir->addChild(newDir);
    std::cout << "Created directory: " << dirname << std::endl;
}

void Terminal::rm(const std::string& name) {
    auto entry = currentDir->findChild(name);
    if (entry) {
        entry->setHidden(true);
        std::cout << "Hidden: " << name << std::endl;
    } else {
        std::cout << "rm: " << name << ": No such file or directory" << std::endl;
    }
}

void Terminal::restore(const std::string& name) {
    auto entry = currentDir->findChild(name);
    if (entry && entry->isHidden()) {
        entry->setHidden(false);
        std::cout << "Restored: " << name << std::endl;
    } else {
        std::cout << "restore: " << name << ": No such hidden file or directory" << std::endl;
    }
}

void Terminal::mv(const std::string& oldName, const std::string& newName) {
    auto entry = currentDir->findChild(oldName);
    if (!entry) {
        std::cout << "mv: " << oldName << ": No such file or directory" << std::endl;
        return;
    }
    if (currentDir->findChild(newName)) {
        std::cout << "mv: " << newName << " already exists" << std::endl;
        return;
    }
    entry->setName(newName);
    std::cout << "Renamed " << oldName << " to " << newName << std::endl;
}

void Terminal::edit(const std::string& filename) {
    auto entry = currentDir->findChild(filename);
    if (!entry) {
        std::cout << "edit: " << filename << ": No such file" << std::endl;
        return;
    }
    entry->edit();
}