#ifndef LIBTDMS_GROUP
#define LIBTDMS_GROUP

#include <memory>
#include <string>
#include <vector>

#include "Channel.h"

class Group
{
public:
    typedef std::vector<std::shared_ptr<Channel>> ChannelSet;

    Group(const std::string &name);
    void addChannel(std::shared_ptr<Channel> channel);

    const std::string &getName() const;
    int getGroupCount() const;
    const ChannelSet &getChannels() const;
    std::shared_ptr<Channel> getChannel(const std::string &name);
    const std::shared_ptr<Channel> getChannel(const std::string &name) const;
    void print(std::ostream &os) const;

private:
    const std::string name;
    ChannelSet channels;
};
#endif // LIBTDMS_GROUP
