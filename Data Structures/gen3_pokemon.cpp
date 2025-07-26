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

std::string to_dec(uint8_t byte, const std::string& prefix) {
    return prefix + std::to_string(byte);
}

std::string bytes_to_hex(uint8_t* arr, int offset, int length, std::string prefix, std::string between) {
    std::string s = "";
    for (int i = length - 1; i >= 0; i--) {
        if (i == length - 1) s += to_hex(arr[offset + i], prefix);
        else s += to_hex(arr[offset + i], between);
    }
    return s;
}

std::string bytes_to_hex(std::vector<uint8_t> arr, int offset, int length, std::string prefix, std::string between) {
    std::string s = "";
    for (int i = length - 1; i >= 0; i--) {
        if (i == length - 1) s += to_hex(arr[offset + i], prefix);
        else s += to_hex(arr[offset + i], between);
    }
    return s;
}

std::string bytes_to_dec(std::vector<uint8_t> arr, int offset, int length) {
    if (length < 1 || length > 8) {
        return "Error: length must be 1 to 8";
    }

    uint64_t value = 0;
    for (int i = 0; i < length; ++i) {
        value |= (uint64_t(arr[offset + i]) << (8 * i));
    }

    return std::to_string(value);
}

std::string bytes_to_dec(uint8_t* arr, int offset, int length) {
    if (length < 1 || length > 8) {
        return "Error: length must be 1 to 8";
    }

    uint64_t value = 0;
    for (int i = 0; i < length; ++i) {
        value |= (uint64_t(arr[offset + i]) << (8 * i));
    }

    return std::to_string(value);
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

std::vector<int8_t> get_values_from_string(std::vector<std::string> s) {
    std::vector<int8_t> values = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < CHAR_LIST.size(); j++) {
            
            // Compare
            if (CHAR_LIST[j] == s[i]) {
                values[i] = j;
                break;
            }
        }
    }

    return values;
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

    void set_field_data(std::vector<uint8_t> growth_data, std::vector<uint8_t> attack_data, std::vector<uint8_t> ev_cond_data, std::vector<uint8_t> misc_data) {
        // Assuming the data parameters are all encrypted
        uint32_t pv = ((uint32_t) full_data[0]) | ((uint32_t) full_data[1] << 8) | ((uint32_t) full_data[2] << 16) | ((uint32_t) full_data[3] << 24); // Little endian
        int mod_pv = pv % 24;
        std::vector<uint8_t> s1, s2, s3, s4;

             if (mod_pv == 0) {s1 = growth_data, s2 = attack_data, s3 = ev_cond_data, s4 = misc_data;}
        else if (mod_pv == 1) {s1 = growth_data, s2 = attack_data, s3 = misc_data, s4 = ev_cond_data;}
        else if (mod_pv == 2) {s1 = growth_data, s2 = ev_cond_data, s3 = attack_data, s4 = misc_data;}
        else if (mod_pv == 3) {s1 = growth_data, s2 = ev_cond_data, s3 = misc_data, s4 = attack_data;}
        else if (mod_pv == 4) {s1 = growth_data, s2 = misc_data, s3 = attack_data, s4 = ev_cond_data;}
        else if (mod_pv == 5) {s1 = growth_data, s2 = misc_data, s3 = ev_cond_data, s4 = attack_data;}

        else if (mod_pv == 6) {s1 = attack_data, s2 = growth_data, s3 = ev_cond_data, s4 = misc_data;}
        else if (mod_pv == 7) {s1 = attack_data, s2 =growth_data , s3 = misc_data, s4 = ev_cond_data;}
        else if (mod_pv == 8) {s1 = attack_data, s2 = ev_cond_data, s3 = growth_data, s4 = misc_data;}
        else if (mod_pv == 9) {s1 = attack_data, s2 = ev_cond_data, s3 = misc_data, s4 = growth_data;}
        else if (mod_pv == 10) {s1 = attack_data, s2 = misc_data, s3 = growth_data, s4 = ev_cond_data;}
        else if (mod_pv == 11) {s1 = attack_data, s2 = misc_data, s3 = ev_cond_data, s4 = growth_data;}

        else if (mod_pv == 12) {s1 = ev_cond_data, s2 = growth_data, s3 = attack_data, s4 = misc_data;}
        else if (mod_pv == 13) {s1 = ev_cond_data, s2 = growth_data, s3 = misc_data, s4 = attack_data;}
        else if (mod_pv == 14) {s1 = ev_cond_data, s2 = attack_data, s3 = growth_data, s4 = misc_data;}
        else if (mod_pv == 15) {s1 = ev_cond_data, s2 = attack_data, s3 = misc_data, s4 = growth_data;}
        else if (mod_pv == 16) {s1 = ev_cond_data, s2 = misc_data, s3 = growth_data, s4 = attack_data;}
        else if (mod_pv == 17) {s1 = ev_cond_data, s2 = misc_data, s3 = attack_data, s4 = growth_data;}

        else if (mod_pv == 18) {s1 = misc_data, s2 = growth_data, s3 = attack_data, s4 = ev_cond_data;}
        else if (mod_pv == 19) {s1 = misc_data, s2 = growth_data, s3 = ev_cond_data, s4 = attack_data;}
        else if (mod_pv == 20) {s1 = misc_data, s2 = attack_data, s3 = growth_data, s4 = ev_cond_data;}
        else if (mod_pv == 21) {s1 = misc_data, s2 = attack_data, s3 = ev_cond_data, s4 = growth_data;}
        else if (mod_pv == 22) {s1 = misc_data, s2 = ev_cond_data, s3 = growth_data, s4 = attack_data;}
        else if (mod_pv == 23) {s1 = misc_data, s2 = ev_cond_data, s3 = attack_data, s4 = growth_data;}


        set_field(FieldData { .offset = 0x20, .length = 12, .value = s1});
        set_field(FieldData { .offset = 0x2C, .length = 12, .value = s2});
        set_field(FieldData { .offset = 0x38, .length = 12, .value = s3});
        set_field(FieldData { .offset = 0x44, .length = 12, .value = s4});
    }

    uint16_t compute_checksum(bool edit_data) {
        // Assuming we need to decrypt the data
        uint32_t pv = ((uint32_t) full_data[0]) | ((uint32_t) full_data[1] << 8) | ((uint32_t) full_data[2] << 16) | ((uint32_t) full_data[3] << 24); // Little endian
        uint32_t ot_id = ((uint32_t) full_data[4]) | ((uint32_t) full_data[5] << 8) | ((uint32_t) full_data[6] << 16) | ((uint32_t) full_data[7] << 24); // Little endian
        uint32_t key = pv ^ ot_id;

        // TODO: Decrypt the data
        uint8_t decrypted_data[48];

        for (int i = 0; i < 48; i += 4) {
            uint32_t chunk = (uint32_t) full_data[0x20 + i] | ((uint32_t) full_data[0x20 + i + 1] << 8) | ((uint32_t) full_data[0x20 + i + 2] << 16) | ((uint32_t) full_data[0x20 + i + 3] << 24);
            chunk ^= key;

            decrypted_data[i] = (uint8_t) (chunk) & 0xFF;
            decrypted_data[i + 1] = (uint8_t) (chunk >> 8) & 0xFF;
            decrypted_data[i + 2] = (uint8_t) (chunk >> 16) & 0xFF;
            decrypted_data[i + 3] = (uint8_t) (chunk >> 24) & 0xFF;
        }

        // Get the checksum
        uint16_t sum = 0;  
        for (int i = 0; i < 48; i += 2) {
            sum += (decrypted_data[i + 1] << 8) | decrypted_data[i];
        }

        if (edit_data) {
            full_data[0x1C] = (uint8_t) (sum & 0xFF);
            full_data[0x1C + 1] = (uint8_t) ((sum >> 8) & 0xFF);
        }
        return sum;
    }

    void encrypt_and_add_data(std::vector<uint8_t> growth_data, std::vector<uint8_t> attack_data, std::vector<uint8_t> ev_cond_data, std::vector<uint8_t> misc_data) {
        // Data parameters are assumed to be unencrypted
        uint32_t pv = ((uint32_t) full_data[0]) | ((uint32_t) full_data[1] << 8) | ((uint32_t) full_data[2] << 16) | ((uint32_t) full_data[3] << 24); // Little endian
        uint32_t ot_id = ((uint32_t) full_data[4]) | ((uint32_t) full_data[5] << 8) | ((uint32_t) full_data[6] << 16) | ((uint32_t) full_data[7] << 24); // Little endian
        uint32_t key = pv ^ ot_id;

        std::vector<uint8_t> combined_data;
        combined_data.reserve(48);
        combined_data.insert(combined_data.end(), growth_data.begin(), growth_data.end());
        combined_data.insert(combined_data.end(), attack_data.begin(), attack_data.end());
        combined_data.insert(combined_data.end(), ev_cond_data.begin(), ev_cond_data.end());
        combined_data.insert(combined_data.end(), misc_data.begin(), misc_data.end());

        for (int i = 0; i < 48; i += 4) {
            uint32_t chunk = (uint32_t) combined_data[i] | ((uint32_t) combined_data[i + 1] << 8) | ((uint32_t) combined_data[i + 2] << 16) | ((uint32_t) combined_data[i + 3] << 24);

            chunk ^= key;
            combined_data[i] = (uint8_t) (chunk & 0xFF);
            combined_data[i + 1] = (uint8_t) ((chunk >> 8) & 0xFF);
            combined_data[i + 2] = (uint8_t) ((chunk >> 16) & 0xFF);
            combined_data[i + 3] = (uint8_t) ((chunk >> 24) & 0xFF);
        }

        std::vector<uint8_t> enc_growth, enc_attack, enc_ev, enc_misc;
        enc_growth.assign(combined_data.begin(), combined_data.begin() + 12);
        enc_attack.assign(combined_data.begin() + 12, combined_data.begin() + 24);
        enc_ev.assign(combined_data.begin() + 24, combined_data.begin() + 36);
        enc_misc.assign(combined_data.begin() + 36, combined_data.begin() + 48);

        set_field_data(enc_growth, enc_attack, enc_ev, enc_misc);
        compute_checksum(true);
    }

    void pretty_print_data() {
        // Assuming we need to decrypt the data
        uint32_t pv = ((uint32_t) full_data[0]) | ((uint32_t) full_data[1] << 8) | ((uint32_t) full_data[2] << 16) | ((uint32_t) full_data[3] << 24); // Little endian
        uint32_t ot_id = ((uint32_t) full_data[4]) | ((uint32_t) full_data[5] << 8) | ((uint32_t) full_data[6] << 16) | ((uint32_t) full_data[7] << 24); // Little endian
        uint32_t key = pv ^ ot_id;

        std::vector<uint8_t> decrypted_data(48);
        for (int i = 0; i < 48; i += 4) {
            uint32_t chunk = (uint32_t) full_data[0x20 + i] | ((uint32_t) full_data[0x20 + i + 1] << 8) | ((uint32_t) full_data[0x20 + i + 2] << 16) | ((uint32_t) full_data[0x20 + i + 3] << 24);
            chunk ^= key;

            decrypted_data[i] = (uint8_t) (chunk) & 0xFF;
            decrypted_data[i + 1] = (uint8_t) (chunk >> 8) & 0xFF;
            decrypted_data[i + 2] = (uint8_t) (chunk >> 16) & 0xFF;
            decrypted_data[i + 3] = (uint8_t) (chunk >> 24) & 0xFF;
        }

        // Split into 4 substructures
        std::vector<std::vector<uint8_t>> slices = {
            {decrypted_data.begin() +  0, decrypted_data.begin() + 12},
            {decrypted_data.begin() + 12, decrypted_data.begin() + 24},
            {decrypted_data.begin() + 24, decrypted_data.begin() + 36},
            {decrypted_data.begin() + 36, decrypted_data.begin() + 48}
        };

        // Define permutation table: 24 rows, each is a permutation of indices [0, 1, 2, 3]
        const std::vector<std::vector<int>> permutations = {
            {0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 1, 2}, {0, 3, 2, 1},
            {1, 0, 2, 3}, {1, 0, 3, 2}, {1, 2, 0, 3}, {1, 2, 3, 0}, {1, 3, 0, 2}, {1, 3, 2, 0},
            {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 1, 0, 3}, {2, 1, 3, 0}, {2, 3, 0, 1}, {2, 3, 1, 0},
            {3, 0, 1, 2}, {3, 0, 2, 1}, {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}
        };


        // Assign based on permutation
        int mod_pv = pv % 24;
        std::vector<uint8_t> growth_data = slices[permutations[mod_pv][0]];
        std::vector<uint8_t> attack_data = slices[permutations[mod_pv][1]];
        std::vector<uint8_t> ev_cond_data = slices[permutations[mod_pv][2]];
        std::vector<uint8_t> misc_data = slices[permutations[mod_pv][3]];

        std::cout << "Decrypted data:";

        std::cout << "\n\tGrowth:\n";
        std::cout << "\t\tSpecies: " << bytes_to_dec(growth_data, 0, 2) << " (" << bytes_to_hex(growth_data, 0, 2, "0x", "") << ")\n";
        std::cout << "\t\tItem held: " << bytes_to_dec(growth_data, 2, 2) << " (" << bytes_to_hex(growth_data, 2, 2, "0x", "") << ")\n";
        std::cout << "\t\tExperience: " << bytes_to_dec(growth_data, 4, 4) << " (" << bytes_to_hex(growth_data, 4, 4, "0x", "") << ")\n";
        std::cout << "\t\tPP bonuses: " << bytes_to_dec(growth_data, 8, 1) << " (" << bytes_to_hex(growth_data, 8, 1, "0x", "") << ")\n";
        std::cout << "\t\tFriendship: " << bytes_to_dec(growth_data, 9, 1) << " (" << bytes_to_hex(growth_data, 9, 1, "0x", "") << ")\n";

        std::cout << "\n\tAttacks:\n";
        std::cout << "\t\tMove 1: " << bytes_to_dec(attack_data, 0, 2) << " (" << bytes_to_hex(attack_data, 0, 2, "0x", "") << ")\n";
        std::cout << "\t\tMove 2: " << bytes_to_dec(attack_data, 2, 2) << " (" << bytes_to_hex(attack_data, 2, 2, "0x", "") << ")\n";
        std::cout << "\t\tMove 3: " << bytes_to_dec(attack_data, 4, 2) << " (" << bytes_to_hex(attack_data, 4, 2, "0x", "") << ")\n";
        std::cout << "\t\tMove 4: " << bytes_to_dec(attack_data, 6, 2) << " (" << bytes_to_hex(attack_data, 6, 2, "0x", "") << ")\n";
        std::cout << "\t\tPP 1: " << bytes_to_dec(attack_data, 8, 1) << " (" << bytes_to_hex(attack_data, 8, 1, "0x", "") << ")\n";
        std::cout << "\t\tPP 2: " << bytes_to_dec(attack_data, 9, 1) << " (" << bytes_to_hex(attack_data, 9, 1, "0x", "") << ")\n";
        std::cout << "\t\tPP 3: " << bytes_to_dec(attack_data, 10, 1) << " (" << bytes_to_hex(attack_data, 10, 1, "0x", "") << ")\n";
        std::cout << "\t\tPP 4: " << bytes_to_dec(attack_data, 11, 1) << " (" << bytes_to_hex(attack_data, 11, 1, "0x", "") << ")\n";

        std::cout << "\n\tEvs and Condition:\n";
        std::cout << "\t\tHP EV: " << bytes_to_dec(ev_cond_data, 0, 1) << " (" << bytes_to_hex(ev_cond_data, 0, 1, "0x", "") << ")\n";
        std::cout << "\t\tAttack EV: " << bytes_to_dec(ev_cond_data, 1, 1) << " (" << bytes_to_hex(ev_cond_data, 1, 1, "0x", "") << ")\n";
        std::cout << "\t\tDefense EV: " << bytes_to_dec(ev_cond_data, 2, 1) << " (" << bytes_to_hex(ev_cond_data, 2, 1, "0x", "") << ")\n";
        std::cout << "\t\tSpeed EV: " << bytes_to_dec(ev_cond_data, 3, 1) << " (" << bytes_to_hex(ev_cond_data, 3, 1, "0x", "") << ")\n";
        std::cout << "\t\tSpecial Attack EV: " << bytes_to_dec(ev_cond_data, 4, 1) << " (" << bytes_to_hex(ev_cond_data, 4, 1, "0x", "") << ")\n";
        std::cout << "\t\tSpecial Defense EV: " << bytes_to_dec(ev_cond_data, 5, 1) << " (" << bytes_to_hex(ev_cond_data, 5, 1, "0x", "") << ")\n";
        std::cout << "\t\tCoolness: " << bytes_to_dec(ev_cond_data, 6, 1) << " (" << bytes_to_hex(ev_cond_data, 6, 1, "0x", "") << ")\n";
        std::cout << "\t\tBeuaty: " << bytes_to_dec(ev_cond_data, 7, 1) << " (" << bytes_to_hex(ev_cond_data, 7, 1, "0x", "") << ")\n";
        std::cout << "\t\tCuteness: " << bytes_to_dec(ev_cond_data, 8, 1) << " (" << bytes_to_hex(ev_cond_data, 8, 1, "0x", "") << ")\n";
        std::cout << "\t\tSmartness: " << bytes_to_dec(ev_cond_data, 9, 1) << " (" << bytes_to_hex(ev_cond_data, 9, 1, "0x", "") << ")\n";
        std::cout << "\t\tToughness: " << bytes_to_dec(ev_cond_data, 10, 1) << " (" << bytes_to_hex(ev_cond_data, 10, 1, "0x", "") << ")\n";
        std::cout << "\t\tFeel: " << bytes_to_dec(ev_cond_data, 11, 1) << " (" << bytes_to_hex(ev_cond_data, 11, 1, "0x", "") << ")\n";

        std::cout << "\n\tMiscellaneous:\n";
        std::cout << "\t\tPokerus status: " << bytes_to_dec(misc_data, 0, 1) << " (" << bytes_to_hex(misc_data, 0, 1, "0x", "") << ")\n";
        std::cout << "\t\tMet location: " << bytes_to_dec(misc_data, 1, 1) << " (" << bytes_to_hex(misc_data, 1, 1, "0x", "") << ")\n";
        std::cout << "\t\tOrigins info: " << bytes_to_dec(misc_data, 2, 2) << " (" << bytes_to_hex(misc_data, 2, 2, "0x", "") << ")\n";
        std::cout << "\t\tIV's, Egg, and Ability: " << bytes_to_dec(misc_data, 4, 4) << " (" << bytes_to_hex(misc_data, 4, 4, "0x", "") << ")\n";
        std::cout << "\t\tRibbons and Obedience: " << bytes_to_dec(misc_data, 8, 4) << " (" << bytes_to_hex(misc_data, 8, 4, "0x", "") << ")\n";
    }

    void pretty_print() {
        std::cout << "Personality value: " << bytes_to_hex(full_data, 0x00, 4, "0x", "") << "\n";
        std::cout << "Oringal trainer ID: " << bytes_to_hex(full_data, 0x04, 4, "0x", "") << "\n";
        std::cout << "Nickname: " << get_character_string(full_data, 0x08, 10) << "\n";
        std::cout << "Language of origin: " << get_language_by_data(full_data[0x12]) << "\n";
        
        // Misc. flags
        std::cout << "Misc. flags: " << bytes_to_hex(full_data, 0x13, 1, "0x", "");
        std::cout << "\n\tis bad egg: " << ((full_data[0x13] & 0x01) ? "true" : "false");
        std::cout << "\n\thas species: " << ((full_data[0x13] & 0x02) ? "true" : "false");
        std::cout << "\n\tuse egg name: " << ((full_data[0x13] & 0x04) ? "true" : "false");
        std::cout << "\n\tblock box RS: " << ((full_data[0x13] & 0x08) ? "true" : "false") << "\n";

        std::cout << "OT Name: " << get_character_string(full_data, 0x14, 7) << "\n";
        
        // Markings
        std::cout << "Markings: " << bytes_to_hex(full_data, 0x1B, 1, "0x", "");
        if (full_data[0x1B] % 16 != 0) std::cout << " (";
        std::cout << ((full_data[0x1B] & 0x01) ? "●" : "");
        std::cout << ((full_data[0x1B] & 0x02) ? "■" : "");
        std::cout << ((full_data[0x1B] & 0x04) ? "▲" : "");
        std::cout << ((full_data[0x1B] & 0x08) ? "♥" : "");
        if (full_data[0x1B] % 16 != 0) std::cout << ")";
        std::cout << "\n";

        std::cout << "Checksum: " << compute_checksum(false) << "\n";
        pretty_print_data();

        std::cout << "Status condition: " << bytes_to_hex(full_data, 0x50, 4, "0x", "") << "\n";
        std::cout << "Level: " << to_dec(full_data[0x54], "") << "\n";
        std::cout << "Mail ID: " << to_dec(full_data[0x55], "") << "\n";

        std::cout << "Current HP: " << bytes_to_dec(full_data, 0x56, 2) << "\n";
        std::cout << "Total HP: " << bytes_to_dec(full_data, 0x58, 2) << "\n";
        std::cout << "Attack: " << bytes_to_dec(full_data, 0x5A, 2) << "\n";
        std::cout << "Defense: " << bytes_to_dec(full_data, 0x5C, 2) << "\n";
        std::cout << "Speed: " << bytes_to_dec(full_data, 0x5E, 2) << "\n";
        std::cout << "Special Attack: " << bytes_to_dec(full_data, 0x60, 2) << "\n";
        std::cout << "Special Defense: " << bytes_to_dec(full_data, 0x62, 2) << "\n";
    }
};

int main() {
    Pokemon_Data pokemon1 = Pokemon_Data();

    FieldData PV = { .offset = 0x00, .length = 4, .value = {0x01, 0x00, 0x00, 0x00} }; // Things are set FROM this value, not vice versa
    FieldData orig_trainer_id = { .offset = 0x04, .length = 4, .value = {0x02, 0x00, 0x00, 0x00} }; // Needs to be set later
    FieldData nickname = { .offset = 0x08, .length = 10, .value = {0xC6, 0xD5, 0xE6, 0xE6, 0xED} };
    FieldData lang = { .offset = 0x12, .length = 1, .value = {2}};
    FieldData misc_flags = { .offset = 0x13, .length = 1, .value = {2}};
    FieldData orig_trainer_name = { .offset = 0x14, .length = 7, .value = {0xCD, 0xDF, 0xDD, 0xE6, 0xE8, 0xE0, 0xD9} };
    FieldData markings = { .offset = 0x1B, .length = 1, .value = {7} };
    FieldData status = { .offset = 0x1B, .length = 4, .value = {0, 0, 0, 0} };
    FieldData level = { .offset = 0x54, .length = 1, .value = {7} };
    FieldData mail_id = { .offset = 0x55, .length = 1, .value = {255} };

    FieldData curr_hp = { .offset = 0x56, .length = 2, .value = {73, 0} };
    FieldData total_hp = { .offset = 0x58, .length = 2, .value = {73, 0} };
    FieldData attack = { .offset = 0x5A, .length = 2, .value = {84, 0} };
    FieldData defense = { .offset = 0x5C, .length = 2, .value = {78, 0} };
    FieldData speed = { .offset = 0x5E, .length = 2, .value = {95, 0} };
    FieldData special_attack = { .offset = 0x60, .length = 2, .value = {119, 0} };
    FieldData special_defense = { .offset = 0x62, .length = 2, .value = {85, 0} };

    pokemon1.set_field(PV);
    pokemon1.set_field(orig_trainer_id);
    pokemon1.set_field(nickname);
    pokemon1.set_field(lang);
    pokemon1.set_field(misc_flags);
    pokemon1.set_field(orig_trainer_name);
    pokemon1.set_field(markings);
    pokemon1.set_field(status);
    pokemon1.set_field(level);
    pokemon1.set_field(mail_id);

    pokemon1.set_field(curr_hp);
    pokemon1.set_field(total_hp);
    pokemon1.set_field(attack);
    pokemon1.set_field(defense);
    pokemon1.set_field(speed);
    pokemon1.set_field(special_attack);
    pokemon1.set_field(special_defense);
    // 0D7, 215
    pokemon1.encrypt_and_add_data(
        {0x9D, 0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B}, 
        {0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17}, 
        {0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23}, 
        {0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F}
    );


    pokemon1.pretty_print();

    /*std::cout << "\n";
    for (int i = 0; i < 100; i++) {
        if (i % 4 == 0) std::cout << to_hex(i, "0x") << ": ";
        std::cout << to_hex(pokemon1.full_data[i], "0x") << " ";
        if (i % 4 == 3) std::cout << "\n"; 
    }
    std::cout << "\n";*/

    return 0;
}