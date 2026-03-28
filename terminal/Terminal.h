#ifndef TERMINAL_H
#define TERMINAL_H

#include <memory>
#include <string>
#include "Directory.h"

class Terminal {
private:
    std::shared_ptr<Directory> root;
    Directory* currentDir;
public:
    Terminal();
    void run();
    void processCommand(const std::string& line);

    void help() const;
    void exit();
    void ls() const;
    void cd(const std::string& path);
    void cat(const std::string& filename);
    void touch(const std::string& filename);
    void mkdir(const std::string& dirname);
    void rm(const std::string& name);
    void restore(const std::string& name);
    void mv(const std::string& oldName, const std::string& newName);
    void edit(const std::string& filename);
};

#endif