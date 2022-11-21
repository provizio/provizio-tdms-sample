#ifndef ROOT_H
#define ROOT_H

#include <memory>
#include <string>
#include <vector>

#include "Group.h"

class Root
{
public:
    typedef std::vector<std::shared_ptr<Group>> GroupSet;
    Root() {}

    int getGroupCount() const;
    const GroupSet &getGroups() const;
    void addGroup(std::shared_ptr<Group> group);
    std::shared_ptr<Group> getGroup(const std::string &name);
    const std::shared_ptr<Group> getGroup(const std::string &name) const;

    void print(std::ostream &os) const;

private:
    GroupSet groups;
};
#endif
