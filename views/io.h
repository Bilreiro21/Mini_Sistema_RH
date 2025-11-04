#ifndef IO_H
#define IO_H

#include "../controllers/rh.h"
#include <string>

namespace IO {
    // Funções de persistência
    bool guardar(const RH& rh, const std::string& filename);
    bool carregar(RH& rh, const std::string& filename);

    // Funções de encriptação/desencriptação (Cifra de César)
    std::string cifrar(const std::string& texto, int chave);
    std::string decifrar(const std::string& texto, int chave);
}

#endif // IO_H