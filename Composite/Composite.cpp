/**
 * @cite Composite Pattern states that the client API should be able to treat both the scalar and composite objects uniformly.
 * Aims at promoting flexibility and scalability by simplifying the client API.
 *
 * @brief Composite Pattern can be exemplified by a FileSystemComponent class that represents a component in a File System.
 * What happens when FileSystemComponent is directory i.e a group of FileSystemComponents ?
 * What happens when we need to add another directory to a directory of FileSystemComponents ?
 */

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Represents a single component in a file system i.e. both a file and a directory.
 * Each File system component must have a basic functionality of printing themselves.
 */
class FileSystemComponent
{
public:
    virtual void display(int offset = 0) = 0;
};

/**
 * @brief Implementation of FileSystemComponent that only repersents a single file.
 */
class File : public FileSystemComponent
{
    std::string filename;

public:
    File(std::string filename) : filename(filename) {}

    // overrides tehe display() funtion to display a single File.
    void display(int offset = 0) override
    {
        std::string indent(offset * 2, ' ');;
        std::cout << indent << (offset == 0 ? "" : "-") << filename << std::endl;
    }
};

/**
 * @brief Implementation of FileSystemComponent that represents a collection of different FileSystemComponents.
 */
class Directory : public FileSystemComponent
{
    std::string directory_name;
    std::vector<FileSystemComponent *> children;

public:
    Directory(std::string name, std::vector<FileSystemComponent *> children = {}) : directory_name(name), children(children) {}
    
    // overrides tehe display() funtion to display a collection of File system components.
    void display(int offset = 0) override
    {
        std::string indent(offset * 2, ' ');
        std::cout << indent << (offset == 0 ? "" : "-") << directory_name << std::endl;
        for (auto child : children)
        {
            child->display(offset + 1);
        }
    }

    // Adds a FileSystemComponent to the directory.
    void add_component(FileSystemComponent *comp)
    {
        children.push_back(comp);
    }
};

int main()
{
    File *hello = new File("Hello.cpp");
    File *world = new File("World.cpp");

    Directory *direc = new Directory("newFolder");
    direc->add_component(hello);
    direc->add_component(world);

    Directory *root = new Directory("Root");
    root->add_component(new File("Temp.cpp"));
    root->add_component(direc);
    
    root->display();
    return 0;
}