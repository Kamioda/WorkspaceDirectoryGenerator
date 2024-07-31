#include "CommandLineArgument.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

struct FileSystemConverter {
    std::filesystem::path operator()(const std::string& str) const {
        return std::filesystem::path(str);
    }
};

inline std::string readJsonFile(const std::filesystem::path& filePath) {
    std::ifstream file(filePath);
    return std::string(std::istream_iterator<char>(file), std::istream_iterator<char>());
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    try {
        const CommandLineArgument CodeWorkspaceFilePath(argv);
        if (!CodeWorkspaceFilePath.exists("file", "f")) throw std::runtime_error("No file path provided");
        const std::filesystem::path TargetPath = CodeWorkspaceFilePath.get<std::filesystem::path, FileSystemConverter>("file", "f");
        if (!std::filesystem::exists(TargetPath)) throw std::runtime_error("File path does not exist");
        const nlohmann::json workspace = nlohmann::json::parse(readJsonFile(TargetPath));
        if (!workspace.contains("folders") || !workspace["folders"].is_array()) throw std::runtime_error("No valid folders key found in JSON file");
        for (const auto& i : workspace["folders"]) {
            if (!i.contains("path") || !i["path"].is_string()) continue;
            const std::filesystem::path folderPath(i["path"].get<std::string>());
            if (!std::filesystem::exists(folderPath)) std::filesystem::create_directories(folderPath);
        }
        return 0;
    }
    catch(const std::exception& er) {
        std::cout << er.what() << std::endl;
        return 1;
    }
}
