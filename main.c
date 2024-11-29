#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void interept(const char * file_name) {
    char full_file_name[256];
    sprintf(full_file_name, "%s.lvs", file_name);
    
    FILE * script = fopen(full_file_name, "r");
    if (script == NULL) {
        perror("LVS: Files Error: file open error");
        return;
    }

    char line[1000];
    while (fgets(line, sizeof(line), script)) {
        if (strstr(line, "put; ") != NULL) {
            char * replaces = strstr(line, "put; ") + strlen("put; ");
            printf("%s\n", replaces);
        } else if (strstr(line, "put;on; ") != NULL) {
            char * replaces = strstr(line, "put;on; ") + strlen("put;on; ");
            char input[1000];
            printf("%s", replaces); 
            fgets(input, sizeof(input), stdin);
            printf("\n");
        } else if (strstr(line, "put;len; ") != NULL) {
            printf("");
            char * replaces = strstr(line, "put;len; ") + strlen("put;len; ");
            size_t length = strlen(replaces);
            if (replaces[length - 1] == '\n') {
                replaces[length - 1] = '\0';
                length--;
            }
            printf("%zu\n", length);
        } else if (strstr(line, "put;os; ") != NULL) {
            char * replaces = strstr(line, "put;os; ") + strlen("put;os; ");
            system(replaces);
            printf("\n");
        } else if (strstr(line, "s;") != NULL) {
            printf("LVS: LVS Target OFF\n");
            exit(0);
        } else if (strstr(line, "error; ") != NULL) {
            char * replaces = strstr(line, "error; ") + strlen("error; ");
            printf("LVS: Error: %s\n", replaces);
        } else if (strstr(line, "sleep; ") != NULL) {
            char * replaces = strstr(line, "sleep; ") + strlen("sleep; ");
            int sleep_seconds = atoi(replaces);
            sleep(sleep_seconds);
        } else if (strstr(line, "panic; ") != NULL) {
            printf("");
            char * replaces = strstr(line, "panic; ") + strlen("panic; ");
            printf("LVS: PANIC: PANIC!(0x1-%s)\n", replaces);
            exit(0);
        } else if (strstr(line, "/n;")) {
            printf("\n");
        } else if (strstr(line, "license;")) {
            printf("\nПроприетарная лицензия LiveStudio НА ПРОДУКТ LVScript.\nГод: 2024\nКомпания: ©LiveStudio\n\nЛицензия предоставляется компании LiveStudio(©) в законном праве распоряжаться ей в полном контексте.\nКомпания не несёт отвественность за ПО которое несёт судебно-исковые последствия,также компания не несёт отвественности за ПО которое было разработано 3-ми лицами, в качестве использования по незаконным действиям\nЛицензия предоставляется 'Как есть' и не распространяема.\nС 4-го января 2025-го года лицензия вступает в силу.\n\nТакже компания не несёт ПОЛНОЙ ОТВЕСТВЕННОСТИ ЗА СОВЕРШЁННЫЕ ДЕЙСТВИЯМИ В СТОРОНУ 3-ИХ ЛИЦ И ИХ СТОРОННИКАМ.\nА также недопустимо КОПИРОВАНИЕ ПРОДУКТА КОМПАНИИ.\n\nLVSLicense(LiveStudioLicense) - 2024 YEAR\n\n©LiveStudio©\n\nЛицензия не распространяема.\n");
        } else if (strstr(line, "/clear;")) {
            printf("\033[0d\033[2J");
        } else if (strstr(line, "after;") != NULL) {
            // PASS
        } else if (strstr(line, "//") != NULL) {
            // Prosto NULL :)
        } else if (strstr(line, "os;name;")){
                #ifdef _WIN32
                printf("Windows 64-bit\n");
                #elif defined(__linux__)
                printf("Linux\n");
                #elif defined(__APPLE__) && defined(__MACH__)
                printf("macOS\n");
                #elif defined(__unix__)
                printf("UNIX\n");
                #elif defined(__CYGWIN__)
                printf("Cygwin\n");
                #else
                printf("-\n");
                #endif
        } else if (strstr(line, "os;exit;")){
            exit(0);
        } else {
            printf("LVS: Find Error: not find a command %s", line);
        }
    fclose(script);
    }
}

int main() {
    interept("main");
    printf("\n");
    return 0;
}