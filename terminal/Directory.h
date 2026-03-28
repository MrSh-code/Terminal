#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Entry.h"
#include <vector>
#include <memory>

class Directory : public Entry {
private:
    std::vector<std::shared_ptr<Entry>> children;
    Directory* parent;

public:
    Directory(const std::string& name, Directory* parent = nullptr);
    ~Directory();

    void list() const override;
    bool isDirectory() const override;
    Directory* asDirectory() override;
    Directory* getDirectory(const std::string& name) const override;

    bool addChild(std::shared_ptr<Entry> child);
    bool removeChild(const std::string& name);
    std::shared_ptr<Entry> findChild(const std::string& name) const;
    Directory* getParent() const;
    void setParent(Directory* parent);
};

#endif