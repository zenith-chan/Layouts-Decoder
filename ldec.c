#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

void en_ru_decode(const wchar_t *english_alphabet, const wchar_t *russian_alphabet, const wchar_t *string) {
    size_t length = wcslen(string);
    wchar_t string_arr[length + 1]; 

    for (size_t i = 0; i < length; ++i) {
        int found = 0;
        for (int j = 0; j < 84; ++j) {
            if (string[i] == english_alphabet[j]) {
                string_arr[i] = russian_alphabet[j];
                found = 1;
                break;
            }
        }
        if (!found) {
            string_arr[i] = string[i];
        }
    }
    string_arr[length] = L'\0';

    wprintf(L"%ls", string_arr);
}

void ru_en_decode(const wchar_t *english_alphabet, const wchar_t *russian_alphabet, const wchar_t *string) {
    size_t length = wcslen(string);
    wchar_t string_arr[length + 1]; 

    for (size_t i = 0; i < length; ++i) {
        int found = 0;
        for (int j = 0; j < 84; ++j) {
            if (string[i] == russian_alphabet[j]) {
                string_arr[i] = english_alphabet[j];
                found = 1;
                break;
            }
        }
        if (!found) {
            string_arr[i] = string[i];
        }
    }
    string_arr[length] = L'\0';

    wprintf(L"%ls", string_arr);
}

int main() {
    setlocale(LC_ALL, "");

    size_t size = 1000;

    wprintf(L"\t\tLayouts Decoder\n");
    wprintf(L" Warning: write '\\' before '\\' and '\"'. ");
    wprintf(L"[^C to exit.]\n\n");
    

//@, #, $, ^, &, ~, `, |, <, > are not supported
    wchar_t english_alphabet[84] = {
        L'F', L'<', L'D', L'U', L'L', L'T', L'~', L':', L'P', L'B',
        L'Q', L'R', L'K', L'V', L'Y', L'J', L'G', L'H', L'C', L'N',
        L'E', L'A', L'{', L'W', L'X', L'I', L'O', L'}', L'S', L'M',
        L'"', L'>', L'Z',
        L'f', L',', L'd', L'u', L'l', L't', L'`', L';', L'p', L'b',
        L'q', L'r', L'k', L'v', L'y', L'j', L'g', L'h', L'c', L'n',
        L'e', L'a', L'[', L'w', L'x', L'i', L'o', L']', L's', L'm',
        L'\'', L'.', L'z',
        L'/', L'?', L'-', L'^', L'$', L'!', L'@', L'#', L'%', L'&', 
        L'*', L'(', L')', L'=', L'+', L'_', L'|', L'\\'        
    };

    wchar_t russian_alphabet[84] = {
        L'А', L'Б', L'В', L'Г', L'Д', L'Е', L'Ё', L'Ж', L'З', L'И',
        L'Й', L'К', L'Л', L'М', L'Н', L'О', L'П', L'Р', L'С', L'Т',
        L'У', L'Ф', L'Х', L'Ц', L'Ч', L'Ш', L'Щ', L'Ъ', L'Ы', L'Ь',
        L'Э', L'Ю', L'Я',
        L'а', L'б', L'в', L'г', L'д', L'е', L'ё', L'ж', L'з', L'и',
        L'й', L'к', L'л', L'м', L'н', L'о', L'п', L'р', L'с', L'т',
        L'у', L'ф', L'х', L'ц', L'ч', L'ш', L'щ', L'ъ', L'ы', L'ь',
        L'э', L'ю', L'я',      
        L'.', L',', L'-', L':', L';', L'!', L'\"', L'№', L'%', L'?',
        L'*', L'(', L')', L'=', L'+', L'_', L'/', L'\\'
    };
    while(1) {
    wprintf(L"Enter your message: ");
    
    wchar_t *main_string = malloc(size * sizeof(wchar_t));
    if (main_string == NULL) {
        wprintf(L"Memory allocation fault\n");
        return 1;
    }

    size_t length = 0;

    while (fgetws(main_string + length, size - length, stdin)) {
        length += wcslen(main_string + length);

        if (length < size - 1 || main_string[length - 1] == L'\n') {
            break;
        }


        size *= 2;

        wchar_t *temp = realloc(main_string, size * sizeof(wchar_t));
        if (temp == NULL) {
            wprintf(L"Memory allocation fault\n");
            free(main_string);
            return 1;
        }

        main_string = temp;

    }

    main_string[wcslen(main_string) - 1] = L'\0';

    wprintf(L"Decoded message is: \"");

    int found = 0;
    for (size_t i = 0; i < wcslen(main_string); ++i) {
        for (int j = 0; j < 84; ++j) {
            if (main_string[i] == russian_alphabet[j]) {
                ru_en_decode(english_alphabet, russian_alphabet, main_string);
                found = 1;
                break;
            } else if (main_string[i] == english_alphabet[j]) {
                en_ru_decode(english_alphabet, russian_alphabet, main_string);
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (!found) {
        wprintf(L"%ls", main_string);
    }
    
    wprintf(L"\"\n\n");
    free(main_string);
    }
    return 0;
}
