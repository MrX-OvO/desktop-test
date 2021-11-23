class File
{
    using Bit = unsigned int;
    Bit mode : 2;
    Bit modified : 1;
    Bit prot_owner : 3;
    Bit prot_group : 3;
    Bit Prot_world : 3;

public:
    enum modes
    {
        READ = 1,
        WRITE,
        EXECUTE
    };
    File &open(modes);
    void close();
    void write();
    void read();
    bool isRead() const;
    void setWrite();
};