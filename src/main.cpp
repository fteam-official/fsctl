#include <iostream>
#include <filesystem>
#include <fstream>

void list_dir(const char* path);
void list_file(const char* path);

int main(int argc, char* argv[]) {
    if (argc == 1) { 
        std::cout << "[?" << std::filesystem::absolute(std::filesystem::current_path()) << "]\n";
        list_dir(std::filesystem::current_path().c_str()); return 0; 
        }

    for (int i = 0; i < argc; i++) {
        if (!std::filesystem::exists(argv[i])) continue;

        std::cout << "[?" << std::filesystem::absolute(argv[i]) << "]\n";

        if (std::filesystem::is_regular_file(argv[i])) {
            list_file(argv[i]);
        } else if (std::filesystem::is_directory(argv[i])) {
            list_dir(argv[i]);
        }
    }
}

void list_dir(const char* path) {
    for (const auto &entry : std::filesystem::directory_iterator(std::filesystem::absolute(path))) {
        std::cout << entry.path().filename() << "\n";
    }
}

void list_file(const char* path) {
    std::ifstream file(path);
    if (!file) return;

    char buf[1024];
    int n = 0;

    while (!file.eof()) {
        file.getline(buf, 1024);
        std::cout << "    | " << buf << '\r';
        std::cout << (++n >= 10000 ? (std::to_string((int)(n/1000)) + 'k') : std::to_string(n).c_str()) << '\n';
    }
    std::cout << '\n';
}