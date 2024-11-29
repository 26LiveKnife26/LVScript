#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

void interpret(const std::string& file_name) {
    std::string full_file_name = file_name + ".lvs";
    
    std::ifstream script(full_file_name);
    if (!script) {
        std::perror("LVS: Files Error: file open error");
        return;
    }

    std::string line;
    while (std::getline(script, line)) {
        if (line.find("put; ") != std::string::npos) {
            std::cout << line.substr(line.find("put; ") + 5) << std::endl;
        } else if (line.find("put;on; ") != std::string::npos) {
            std::cout << line.substr(line.find("put;on; ") + 8);
            std::string input;
            std::getline(std::cin, input);
            std::cout << std::endl;
        } else if (line.find("put;len; ") != std::string::npos) {
            std::string replaces = line.substr(line.find("put;len; ") + 9);
            if (!replaces.empty() && replaces.back() == '\n') {
                replaces.pop_back();
            }
            std::cout << replaces.length() << std::endl;
        } else if (line.find("put;os; ") != std::string::npos) {
            std::system(line.substr(line.find("put;os; ") + 8).c_str());
            std::cout << std::endl;
        } else if (line.find("s;") != std::string::npos) {
            std::cout << "LVS: LVS Target OFF" << std::endl;
            std::exit(0);
        } else if (line.find("error; ") != std::string::npos) {
            std::cout << "LVS: Error: " << line.substr(line.find("error; ") + 7);
        } else if (line.find("sleep; ") != std::string::npos) {
            int sleep_seconds = std::stoi(line.substr(line.find("sleep; ") + 7));
            sleep(sleep_seconds);
        } else if (line.find("panic; ") != std::string::npos) {
            std::cout << "LVS: PANIC: PANIC!(0x1-" << line.substr(line.find("panic; ") + 7) << ")" << std::endl;
            std::exit(0);
        } else if (line.find("/n;") != std::string::npos) {
            std::cout << std::endl;
        } else if (line.find("license;") != std::string::npos) {
            std::cout << "\nПроприетарная лицензия LiveStudio НА ПРОДУКТ LVScript.\nГод: 2024\nКомпания: ©LiveStudio\n\nЛицензия предоставляется компании LiveStudio(©) в законном праве распоряжаться ей в полном контексте.\nКомпания не несёт отвественность за ПО которое несёт судебно-исковые последствия,также компания не несёт отвественности за ПО которое было разработано 3-ми лицами, в качестве использования по незаконным действиям\nЛицензия предоставляется 'Как есть' и не распространяема.\nС 4-го января 2025-го года лицензия вступает в силу.\n\nТакже компания не несёт ПОЛНОЙ ОТВЕСТВЕННОСТИ ЗА СОВЕРШЁННЫЕ ДЕЙСТВИЯМИ В СТОРОНУ 3-ИХ ЛИЦ И ИХ СТОРОННИКАМ.\nА также недопустимо КОПИРОВАНИЕ ПРОДУКТА КОМПАНИИ.\n\nLVSLicense(LiveStudioLicense) - 2024 YEAR\n\n©LiveStudio©\n\nЛицензия не распространяема.\n";
        } else if (line.find("/clear;") != std::string::npos) {
            std::cout << "\033[0d\033[2J";
        } else if (line.find("after;") != std::string::npos) {
            // PASS
        } else if (line.find("//") != std::string::npos) {
            // Prosto NULL :)
        } else if (line.find("os;name;") != std::string::npos) {
            #ifdef _WIN32
            std::cout << "Windows 64-bit" << std::endl;
            #elif defined(__linux__)
            std::cout << "Linux" << std::endl;
            #elif defined(__APPLE__) && defined(__MACH__)
            std::cout << "macOS" << std::endl;
            #elif defined(__unix__)
            std::cout << "UNIX" << std::endl;
            #elif defined(__CYGWIN__)
            std::cout << "Cygwin" << std::endl;
            #else
            std::cout << "-" << std::endl;
            #endif
        } else if (line.find("os;exit;") != std::string::npos) {
            std::exit(0);
        } else {
            std::cout << "LVS: Find Error: not find a command " << line;
        }
    }
    script.close();
}

int main() {
    interpret("main");
    std::cout << std::endl;
    return 0;
}

