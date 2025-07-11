#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <string>
#include <sstream>

const std::vector<std::string> CHAR_LIST = {
    " ", "À", "Á", "Â", "Ç", "È", "É", "Ê", "Ë", "Ì", " ", "Î", "Ï", "Ò", "Ó", "Ô",
    "Œ", "Ù", "Ú", "Û", "Ñ", "ß", "à", "á", " ", "ç", "è", "é", "ê", "ë", "ì", " ",
    "î", "ï", "ò", "ó", "ô", "œ", "ù", "ú", "û", "ñ", "º", "ª", "ᵉʳ", "&", "+", " ",
    " ", " ", " ", " ", "Lv", "=", ";", " ", " ", " ", " ", " ", " ", " ", " ", " ",
    " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
    "▯", "¿", "¡", "PK", "MM", " ", " ", " ", " ", " ", "Í", "%", "(", ")", " ", " ",
    " ", " ", " ", " ", " ", " ", " ", " ", "â", " ", " ", " ", " ", " ", " ", "í",
    " ", " ", " ", " ", " ", " ", " ", " ", " ", "↑", "↓", "←", "→", "*", "*", "*",
    "*", "*", "*", "*", "ᵉ", "<", ">", " ", " ", " ", " ", " ", " ", " ", " ", " ",
    " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
    "ʳᵉ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "!", "?", ".", "-", "･",
    "‥", "“", "”", "‘", "'", "♂", "♀", "$", ",", "×", "/", "A", "B", "C", "D", "E",
    "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
    "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "►",
    ":", "Ä", "Ö", "Ü", "ä", "ö", "ü", " ", " ", " ", " ", " ", " ", " ", " ", " ",
};

std::string to_hex(uint8_t byte, std::string prefix) {
    std::ostringstream oss;
    oss << prefix
        << std::hex << std::uppercase
        << std::setw(2) << std::setfill('0')
        << static_cast<int>(byte);
    return oss.str();
}

std::string bytes_to_hex(uint8_t* arr, int offset, int length, std::string prefix, std::string between) {
    std::string s = "";
    for (int i = 0; i < length; i++) {
        s += to_hex(arr[offset + i], prefix);
        if (i != length - 1) s += between;
    }

    return s;
}

std::string get_character_string(uint8_t* data, int offset, int length) {
    std::string s = "";

    for (int i = 0; i < length; i++) {
        s += CHAR_LIST[data[offset + i]];
    }

    return s;
}

std::string get_language_by_data(uint8_t lang_index) {
    std::vector<std::string> languages = {"", "Japanese", "English", "French", "Italian", "German", "unused", "Spanish"};
    return languages[lang_index];
}

typedef struct {
    int offset;
    int length;
    std::vector<uint8_t> value;
} FieldData;

class Pokemon_Data {
    public: 
    uint8_t* full_data;

    public:
    Pokemon_Data() {
        full_data = (uint8_t*) malloc(100 * sizeof(uint8_t));
        if (full_data == nullptr) throw std::bad_alloc();
        memset(full_data, 0, 100);
    }

    ~Pokemon_Data() {
        free(full_data);
    }

    void set_field(FieldData data) {
        for (int i = 0; i < data.length; i++) {
            full_data[data.offset + i] = data.value[i];
        }
    }

    void pretty_print() {
        std::cout << "Personality value: " << bytes_to_hex(full_data, 0x00, 4, "", "") << "\n";
        std::cout << "Oringal trainer ID: " << bytes_to_hex(full_data, 0x04, 4, "0x", " ") << "\n";
        std::cout << "Nickname: " << get_character_string(full_data, 0x08, 10) << "\n";
        std::cout << "Language of origin: " << get_language_by_data(full_data[0x12]) << "\n";
        std::cout << "Misc. flags:\n\tis bad egg: " << "\n";
    }
};

int main() {
    Pokemon_Data pokemon1 = Pokemon_Data();

    FieldData PV = {
         .offset = 0x00,
         .length = 4,
         .value = {65, 66, 67, 68}
    };

    FieldData nickname = {
        .offset = 0x08,
        .length = 10,
        .value = {0xC6, 0xD5, 0xE6, 0xE6, 0xED}
    };

    FieldData lang = {.offset = 0x12, .length = 1, .value = {2}};

    pokemon1.set_field(PV);
    pokemon1.set_field(nickname);
    pokemon1.set_field(lang);

    pokemon1.pretty_print();

    return 0;
}