#ifndef POSTPONEDFILE_H
#define POSTPONEDFILE_H

#include "Entry.h"
#include <memory>
#include <vector>
#include <string>

class PostponedFile : public Entry {
private:
    std::shared_ptr<Entry> actualFile;
public:
    PostponedFile(const std::string& name);
    ~PostponedFile();

    std::string getName() const override;
    void setName(const std::string& newName) override;
    bool isHidden() const override;
    void setHidden(bool hidden) override;
    void printContent() const override;
    void edit() override;
    void list() const override;
    bool isDirectory() const override;
    Directory* asDirectory() override;
    Directory* getDirectory(const std::string& name) const override;

    void realizeAsSingle(const std::string& content);
    void realizeAsMulti(const std::vector<std::string>& lines);
};

#endif