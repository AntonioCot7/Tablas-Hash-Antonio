#ifndef TABLAHASH_HASH_TABLE_H
#define TABLAHASH_HASH_TABLE_H

#include <iostream>

template <typename K, typename V>
struct KeyValuePair {
    K key;
    V value;

    // Constructor
    KeyValuePair() {}
    KeyValuePair(const K& key, const V& value) : key(key), value(value) {}

    // Sobrecargar operador de comparación
    bool operator==(const K& otherKey) const {
        return key == otherKey;
    }
};

template <typename K, typename V>
class HashTable {
private:
    KeyValuePair<K, V>* table;
    bool* is_occupied;
    int capacity;
    int size;

    // Parámetros para la función de hashing universal
    int a;
    int b;
    int prime;

    // Función de hashing universal
    int hash(const K& key) const {
        if constexpr (std::is_arithmetic<K>::value) {
            // Hash para enteros (usando la fórmula universal de hashing)
            return ((a * key + b) % prime) % capacity;  // Hash para enteros u otros tipos numéricos
        } else {
            // Hash para cadenas (std::string)
            int hash_value = 0;
            for (char c : key) {
                hash_value = (hash_value * 31 + c) % prime;  // Usa 31 como base para hashing de cadenas
            }
            return hash_value % capacity;  // Aseguramos que caiga dentro de la capacidad
        }
    }


    void resize();

public:
    HashTable(int cap, int prime_val = 31);
    ~HashTable();

    bool insert(const K& key, const V& value);
    V search(const K& key) const;
    bool remove(const K& key);
    void empty();
    int get_size() const;

    std::pair<bool, int> search_with_probes(const K& key) const;

    // Función para imprimir la tabla hash
    void print_table() const;
};

// Constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(int cap, int prime_val) : capacity(cap), size(0), prime(prime_val) {
    table = new KeyValuePair<K, V>[capacity];
    is_occupied = new bool[capacity];
    for (int i = 0; i < capacity; ++i) {
        is_occupied[i] = false;
    }

    // Generar valores aleatorios para a y b solo una vez
    a = rand() % (prime - 1) + 1; // Asegurarse de que a sea positivo
    b = rand() % prime;
}

// Destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    delete[] table;
    delete[] is_occupied;
}

// Función para insertar un par clave-valor en la tabla hash
template <typename K, typename V>
bool HashTable<K, V>::insert(const K& key, const V& value) {
    if (size >= capacity / 2) {
        resize(); // Redimensionar si la tabla está medio llena
    }

    int index = hash(key); // Calcula el índice con la función de hash universal
    for (int i = 0; i < capacity; ++i) {
        int probing_index = (index + i) % capacity; // Resolución de colisiones por sondeo
        if (!is_occupied[probing_index]) {
            table[probing_index] = KeyValuePair<K, V>(key, value); // Inserta el par clave-valor
            is_occupied[probing_index] = true;
            size++;
            return true;
        }
    }
    return false;  // Si la tabla está llena
}

// Función para buscar un valor por clave
template <typename K, typename V>
V HashTable<K, V>::search(const K& key) const {
    int index = hash(key);  // Calcula el índice inicial con la función de hash
    for (int i = 0; i < capacity; ++i) {
        int probing_index = (index + i) % capacity;  // Calcula el índice en la tabla con sondeo
        if (!is_occupied[probing_index]) {  // Si la posición está vacía
            return V();  // Retorna un valor por defecto del tipo V (no encontrado)
        }
        if (table[probing_index].key == key) {  // Si la clave coincide
            return table[probing_index].value;  // Retorna el valor encontrado
        }
    }
    return V();  // Si no se encontró el valor, retorna un valor por defecto
}

template <typename K, typename V>
std::pair<bool, int> HashTable<K, V>::search_with_probes(const K& key) const {
    int index = hash(key);  // Calcula el índice inicial con la función de hash universal
    int probes = 0;  // Contador de sondeos

    for (int i = 0; i < capacity; ++i) {
        probes++;  // Incrementamos el número de sondeos en cada intento
        int probing_index = (index + i) % capacity;  // Calcula el índice en la tabla con sondeo

        if (!is_occupied[probing_index]) {  // Si la posición está vacía, no está el valor
            return std::make_pair(false, probes);  // No encontrado, devolvemos false y el número de sondeos
        }

        if (table[probing_index].key == key) {  // Si la clave coincide
            return std::make_pair(true, probes);  // Encontrado, devolvemos true y el número de sondeos
        }
    }

    return std::make_pair(false, probes);  // Si no se encontró el valor después de recorrer la tabla
}

// Función para eliminar un elemento de la tabla hash
template <typename K, typename V>
bool HashTable<K, V>::remove(const K& key) {
    int index = hash(key);
    for (int i = 0; i < capacity; ++i) {
        int probing_index = (index + i) % capacity;
        if (!is_occupied[probing_index]) {
            return false;  // No encontrado
        }
        if (table[probing_index].key == key) {
            is_occupied[probing_index] = false;
            size--;
            return true;  // Eliminado
        }
    }
    return false;
}

// Función para vaciar la tabla hash
template <typename K, typename V>
void HashTable<K, V>::empty() {
    for (int i = 0; i < capacity; ++i) {
        is_occupied[i] = false;
    }
    size = 0;
}

// Función para obtener el tamaño de la tabla
template <typename K, typename V>
int HashTable<K, V>::get_size() const {
    return size;
}

// Función para redimensionar (rehashing)
template <typename K, typename V>
void HashTable<K, V>::resize() {
    int new_capacity = capacity * 2;
    KeyValuePair<K, V>* new_table = new KeyValuePair<K, V>[new_capacity];
    bool* new_is_occupied = new bool[new_capacity];

    for (int i = 0; i < new_capacity; ++i) {
        new_is_occupied[i] = false;
    }

    // Rehashing
    for (int i = 0; i < capacity; ++i) {
        if (is_occupied[i]) {
            int new_index = hash(table[i].key); // Usa la función hash correcta según el tipo
            for (int j = 0; j < new_capacity; ++j) {
                int probing_index = (new_index + j) % new_capacity;
                if (!new_is_occupied[probing_index]) {
                    new_table[probing_index] = table[i];
                    new_is_occupied[probing_index] = true;
                    break;
                }
            }
        }
    }

    delete[] table;
    delete[] is_occupied;

    table = new_table;
    is_occupied = new_is_occupied;
    capacity = new_capacity;
}


// Función para imprimir toda la tabla hash
template <typename K, typename V>
void HashTable<K, V>::print_table() const {
    std::cout << "Contenido de la tabla hash:" << std::endl;
    for (int i = 0; i < capacity; ++i) {
        if (is_occupied[i]) {
            std::cout << "Índice " << i << ": (" << table[i].key << ", " << table[i].value << ")" << std::endl;
        } else {
            std::cout << "Índice " << i << ": Vacío" << std::endl;
        }
    }
    std::cout << "Tamaño actual: " << size << std::endl;
}

#endif // TABLAHASH_HASH_TABLE_H
