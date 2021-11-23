/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-09 16:21:26
 * @LastEditTime : 2021-08-09 17:27:50
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testclassdesign/test05.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <string>
#include <set>

class Folder;
class Message
{
    friend class Folder;
    friend void swap(Message &, Message &);

private:
    std::string contents;       // 消息文本
    std::set<Folder *> folders; // 包含本Message的Folder

private:
    void add_to_folders(const Message &); // 将本Message存放到Folder中
    void remove_from_folders();           // 将本Message从Folder中移除

public:
    explicit Message(const std::string &str = "") : contents(str) {}
    Message(const Message &);
    Message &operator=(const Message &);
    ~Message();
    void save(Folder &);         // 从给定Folder集合中添加本Message
    void remove(Folder &);       // 从给定Folder集合中删除本Message
    void addFolder(Folder &);    // 向folders添加一个给定的Folder*
    void removeFolder(Folder &); // 向folders删除一个给定的Folder*
};

inline void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto &&f : lhs.folders)
        f->removeMsg(lhs);
    for (auto &&f : rhs.folders)
        f->removeMsg(rhs);
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);
    for (auto &&f : lhs.folders)
        f->addMsg(lhs);
    for (auto &&f : rhs.folders)
        f->addMsg(rhs);
}

inline void Message::add_to_folders(const Message &m)
{
    for (auto &&f : m.folders)
        f->addMsg(*this);
}

inline void Message::remove_from_folders()
{
    for (auto &&f : folders)
        f->removeMsg(*this);
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) { add_to_folders(m); }

Message &Message::operator=(const Message &rhs)
{
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}

Message::~Message() { remove_from_folders(); }

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(*this);
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.removeMsg(*this);
}

void Message::addFolder(Folder &f) { folders.insert(&f); }

void Message::removeFolder(Folder &f) { folders.erase(&f); }

class Folder
{
private:
    std::set<Message *> messages;

public:
    Folder() = default;
    ~Folder() {}
    void addMsg(Message &);
    void removeMsg(Message &);
};

void Folder::addMsg(Message &m)
{
    messages.insert(&m);
    m.addFolder(*this);
}

void Folder::removeMsg(Message &m)
{
    messages.erase(&m);
    m.removeFolder(*this);
}

int main(int argc, char const *argv[])
{

    return 0;
}
