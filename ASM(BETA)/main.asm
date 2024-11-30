section .data
    file_extension db ".lvs", 0
    error_msg db "LVS: Files Error: file open error", 0
    put_str db "put; ", 0
    put_on_str db "put;on; ", 0
    put_len_str db "put;len; ", 0
    put_os_str db "put;os; ", 0
    s_str db "s;", 0
    lvs_off_msg db "LVS: LVS Target OFF", 10, 0
    error_str db "error; ", 0
    lvs_error_msg db "LVS: Error: ", 0
    sleep_str db "sleep; ", 0
    panic_str db "panic; ", 0
    lvs_panic_msg db "LVS: PANIC: PANIC!(0x1-", 0
    newline_str db "/n;", 0
    license_str db "license;", 0
    license_text db 10, "Проприетарная лицензия LiveStudio НА ПРОДУКТ LVScript.", 10, "Год: 2024", 10, "Компания: ©LiveStudio", 10, 10, "Лицензия предоставляется компании LiveStudio(©) в законном праве распоряжаться ей в полном контексте.", 10, "Компания не несёт отвественность за ПО которое несёт судебно-исковые последствия,также компания не несёт отвественности за ПО которое было разработано 3-ми лицами, в качестве использования по незаконным действиям", 10, "Лицензия предоставляется 'Как есть' и не распространяема.", 10, "С 4-го января 2025-го года лицензия вступает в силу.", 10, 10, "Также компания не несёт ПОЛНОЙ ОТВЕСТВЕННОСТИ ЗА СОВЕРШЁННЫЕ ДЕЙСТВИЯМИ В СТОРОНУ 3-ИХ ЛИЦ И ИХ СТОРОННИКАМ.", 10, "А также недопустимо КОПИРОВАНИЕ ПРОДУКТА КОМПАНИИ.", 10, 10, "LVSLicense(LiveStudioLicense) - 2024 YEAR", 10, 10, "©LiveStudio©", 10, 10, "Лицензия не распространяема.", 10, 0
    clear_str db "/clear;", 0
    clear_seq db 27, "[0d", 27, "[2J", 0
    after_str db "after;", 0
    comment_str db "//", 0
    os_exit_str db "os;exit;", 0
    find_error_msg db "LVS: Find Error: not find a command ", 0
    main_file db "main", 0

section .text
    global _start

extern fopen, fclose, fgets, printf, puts, exit, system, sleep, strlen

_start:
    push main_file
    call interpret
    add esp, 4

    push 10
    call putchar
    add esp, 4

    mov eax, 1
    xor ebx, ebx
    int 0x80

interpret:
    push ebp
    mov ebp, esp
    sub esp, 256  ; Local buffer for file name and line

    mov eax, [ebp+8]  ; Get file_name argument
    mov ecx, file_extension
    lea edi, [ebp-256]
    call strcat

    push 0
    push edi
    call fopen
    add esp, 8
    test eax, eax
    jz file_error

    mov [ebp-4], eax  ; Store file handle

read_loop:
    ; Read line from file
    push dword [ebp-4]
    push 256
    lea eax, [ebp-256]
    push eax
    call fgets
    add esp, 12
    test eax, eax
    jz end_of_file

    lea esi, [ebp-256]
    call process_line

    jmp read_loop

file_error:
    push error_msg
    call puts
    add esp, 4
    jmp interpret_end

end_of_file:
    push dword [ebp-4]
    call fclose
    add esp, 4

interpret_end:
    mov esp, ebp
    pop ebp
    ret

process_line:
    push put_str
    push esi
    call strstr
    add esp, 8
    test eax, eax
    jz check_next_command

    add eax, 5
    push eax
    call puts
    add esp, 4
    ret

check_next_command:
    push esi
    push find_error_msg
    call printf
    add esp, 8

    ret