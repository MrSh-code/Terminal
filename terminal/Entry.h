#ifndef ENTRY_H
#define ENTRY_H

#include <string>

class Directory; // forward declaration

class Entry {
protected:
    std::string name;
    bool hidden;

public:
    Entry(const std::string& name);
    virtual ~Entry();

    virtual std::string getName() const;
    virtual void setName(const std::string& newName);
    virtual bool isHidden() const;
    virtual void setHidden(bool hidden);

    virtual void printContent() const;
    virtual void edit();
    virtual void list() const;
    virtual bool isDirectory() const;
    virtual Directory* asDirectory(); // для получения указателя на Directory, если это директория
    virtual Directory* getDirectory(const std::string& name) const;
};

#endif