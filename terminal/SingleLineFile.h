#ifndef SINGLELINEFILE_H
#define SINGLELINEFILE_H

#include "Entry.h"
#include <string>

class SingleLineFile : public Entry {
private:
    std::string content;
public:
    SingleLineFile(const std::string& name, const std::string& content = "");
    void printContent() const override;
    void edit() override;
};

#endif