
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

class Directory {
public:
    string name;
    map<string, Directory*> directories;
    map<string, string> files;
    Directory* parent;

    Directory(string n, Directory* p)
        : name(n), parent(p) {}

    Directory* getDirectory(string n) {
        if (n == "..") {
            return parent;
        } else if (n == "/") {
            Directory* temp = this;
            while (temp->parent != nullptr) {
                temp = temp->parent;
            }
            return temp;
        } else {
            if (directories.find(n) != directories.end()) {
                return directories[n];
            } else {
                cout << "Directory not found: " << n << endl;
                return nullptr;
            }
        }
    }

    void createDirectory(string n) {
        Directory* newDir = new Directory(n, this);
        directories[n] = newDir;
    }

    void createFile(string n) {
        if (files.find(n) != files.end()) {
            cout << "File already exists: " << n << endl;
        } else {
            files[n] = "";
        }
    }

    void deleteFile(string n) {
        if (files.find(n) != files.end()) {
            files.erase(n);
        } else {
            cout << "File not found: " << n << endl;
        }
    }

    void printContents() {
        cout << "Directories:" << endl;
        for (auto const& pair : directories) {
            cout << pair.first << endl;
        }
        cout << "Files:" << endl;
        for (auto const& pair : files) {
            cout << pair.first << endl;
        }
    }
};

class FileSystem {
private:
    Directory* currentDirectory;

public:
    FileSystem() {
        currentDirectory = new Directory("/", nullptr);
    }

    void processCommand(string command) {
        stringstream ss(command);
        string operation;
        ss >> operation;

        if (operation == "mkdir") {
            string directoryName;
            ss >> directoryName;
            currentDirectory->createDirectory(directoryName);
        } else if (operation == "cd") {
            string directoryName;
            ss >> directoryName;
            currentDirectory = currentDirectory->getDirectory(directoryName);
        } else if (operation == "ls") {
            currentDirectory->printContents();
        } else if (operation == "touch") {
            string fileName;
            ss >> fileName;
            currentDirectory->createFile(fileName);
        } else if (operation == "rm") {
            string fileName;
            ss >> fileName;
            currentDirectory->deleteFile(fileName);
        } else {
            cout << "Invalid command: " << operation << endl;
        }
    }
};

int main() {
    FileSystem fs;

    while (true) {
        string command;
        cout << "> ";
        getline(cin, command);

        if (command == "exit") {
            break;
        }

        fs.processCommand(command);
    }

    return 0;
}

