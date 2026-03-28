#ifndef MULTILINEFILE_H
#define MULTILINEFILE_H

#include "Entry.h"
#include <vector>
#include <string>

class MultiLineFile : public Entry {
private:
    std::vector<std::string> lines;
public:
    MultiLineFile(const std::string& name, const std::vector<std::string>& lines = {});
    void printContent() const override;
    void edit() override;
};

#endif