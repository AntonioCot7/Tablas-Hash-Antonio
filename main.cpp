#include <iostream>
#include "hash_table.h"

int main() {
    HashTable<int, std::string> hash_table(20);  // Capacidad inicial de 20

    // Insertar elementos
    hash_table.insert(10, "Diez");
    hash_table.insert(22, "Veinte");
    hash_table.insert(31, "Treinta y uno");
    hash_table.insert(84, "Ochenta y cuatro");
    hash_table.insert(43, "Cuarenta y tres");
    hash_table.insert(33, "Treinta y cuatro");
    hash_table.insert(76, "Setenta y seis");
    hash_table.insert(12, "Doce");
    hash_table.insert(39, "Treinta y nueve");
    hash_table.insert(45, "Cuarenta y cincooo");
    hash_table.insert(45, "Cuarenta y cinco");




    // Buscar elementos con número de recorridos
    auto result = hash_table.search_with_probes(31);
    std::cout << "31 encontrado: " << (result.first ? "Sí" : "No") << ", Recorridos: " << result.second << std::endl;

    result = hash_table.search_with_probes(22);
    std::cout << "22 encontrado: " << (result.first ? "Sí" : "No") << ", Recorridos: " << result.second << std::endl;

    // Eliminar elemento
    hash_table.remove(22);
    result = hash_table.search_with_probes(22);
    std::cout << "22 encontrado: " << (result.first ? "Sí" : "No") << ", Recorridos: " << result.second << std::endl;

    auto result10 = hash_table.search_with_probes(84);
    std::cout << "84 encontrado: " << (result10.first ? "Sí" : "No") << ", Recorridos: " << result10.second << std::endl;

    // Imprimir tabla hash
    hash_table.print_table();

    auto result2 = hash_table.search_with_probes(45);
    std::cout << "45 encontrado: " << (result2.first ? "Sí" : "No") << ", Recorridos: " << result2.second << std::endl;

    auto result3 = hash_table.search(12);
    std::cout << result3 << std::endl;

    auto result4= hash_table.search_with_probes(45);
    std::cout << "45 encontrado: " << (result4.first ? "Sí" : "No") << ", Recorridos: " << result4.second << std::endl;

    auto result5 = hash_table.search(45);
    std::cout << result5 << std::endl;

    auto result6 = hash_table.search(45);
    std::cout << result6 << std::endl;

    // Vaciar la tabla
    hash_table.empty();
    std::cout << "Tamaño actual: " << hash_table.get_size() << std::endl;
    return 0;
}
