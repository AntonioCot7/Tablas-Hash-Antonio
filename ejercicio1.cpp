#include <iostream>
#include <string>
#include "hash_table.h" // El archivo que proporcionaste

std::string morse_codes[26] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
        "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

// Función para convertir una palabra a su transformación Morse
std::string toMorse(const std::string& word, const std::string morse_codes[]) {
    std::string morse_representation;
    for (char c : word) {
        morse_representation += morse_codes[c - 'a']; // Obtener código Morse para la letra
    }
    return morse_representation;
}

int main() {
    std::string words[] = {"gin", "zen", "gig", "msg"}; // Ejemplo de palabras
    int num_words = sizeof(words) / sizeof(words[0]);

    // Crear la tabla hash
    HashTable<std::string, int> hash_table(10);

    // Insertar las transformaciones Morse en la tabla hash
    for (int i = 0; i < num_words; ++i) {
        std::string morse_word = toMorse(words[i], morse_codes);
        hash_table.insert(morse_word, 1); // Insertar en la tabla hash
    }

    // Imprimir el número de transformaciones únicas
    std::cout << "Número de transformaciones únicas: " << hash_table.get_size() << std::endl;

    return 0;
}
