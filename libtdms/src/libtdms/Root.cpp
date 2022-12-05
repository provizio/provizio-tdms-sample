#include "libtdms/Root.h"
#include "libtdms/Group.h"
#include <iostream>

void Root::addGroup(std::shared_ptr<Group> group)
{
    // for (GroupSet::iterator iter = groups.begin(); iter != groups.end();
    //      ++iter) {
    //   if ((**iter) == (*group)) return;
    // }
    groups.push_back(group);
}

std::shared_ptr<Group> Root::getGroup(const std::string &name)
{
    for (GroupSet::iterator iter = groups.begin(); iter != groups.end();
         ++iter)
    {
        if ((*iter)->getName() == name)
            return *iter;
    }
    return 0;
}

const std::shared_ptr<Group> Root::getGroup(const std::string &name) const
{
    for (GroupSet::const_iterator iter = groups.begin(); iter != groups.end();
         ++iter)
    {
        if ((*iter)->getName() == name)
            return *iter;
    }
    return 0;
}

void Root::print(std::ostream &os) const
{
    os << "\nThere are " << groups.size() << " groups." << std::endl;
    for (GroupSet::const_iterator group = groups.begin();
         group != groups.end(); ++group)
    {
        (*group)->print(os);
    }
}

int Root::getGroupCount() const
{
    return groups.size();
}

const Root::GroupSet &Root::getGroups() const
{
    return groups;
}
