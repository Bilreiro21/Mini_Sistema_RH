# ﻿Mini Sistema RH - Gestão de Férias e Faltas
📋 Descrição
Sistema de gestão de recursos humanos para controlo de férias e faltas de colaboradores, com visualização de calendário mensal e persistência de dados encriptados.
✨ Funcionalidades

✅ Adicionar colaboradores (sem duplicados)
✅ Marcar férias (F) e faltas (X) por data
✅ Desmarcar dias específicos
✅ Listar todos os colaboradores
✅ Visualizar calendário mensal com:

Férias marcadas (F)
Faltas marcadas (X)
Fins de semana identificados (-)


✅ Validações:

Datas válidas (incluindo anos bissextos)
Não permite marcar fins de semana
Previne colaboradores duplicados


✅ Persistência de dados:

Gravação automática ao sair
Carregamento automático ao iniciar
Encriptação dos nomes (Cifra de César)



🛠️ Compilação
Opção 1: Compilação Manual
Linux/Mac:
bashg++ -std=c++11 -Wall -o mini_rh main.cpp colaborador.cpp rh.cpp utils.cpp io.cpp
./mini_rh
Windows (MinGW):
bashg++ -std=c++11 -Wall -o mini_rh.exe main.cpp colaborador.cpp rh.cpp utils.cpp io.cpp
mini_rh.exe


# 📂 Estrutura do Projeto

```
MINI_SISTEMA_RH/
├── controllers/
│   ├── rh.cpp          # Classe RH (gestão de colaboradores)
│   └── rh.h
│
├── models/
│   ├── colaborador.cpp # Classe Colaborador e marcações
│   ├── colaborador.h
│   ├── utils.cpp       # Funções auxiliares (datas, validações)
│   └── utils.h
│
├── views/
│   ├── cores.h         # Cores para o menu
│   ├── io.cpp          # Persistência e encriptação
│   └── io.h
│
├── .gitignore
├── main.cpp            # Interface e menu principal
├── dados_rh.txt        # (gerado/atualizado pelo programa)
└── mini_rh.exe         # (resultado da compilação no Windows)
```

#🎯 Como Usar
Menu Principal

===== MINI-SISTEMA RH =====
1. Adicionar colaborador
2. Listar colaboradores
3. Marcar FERIAS (F)
4. Marcar FALTA (X)
5. Desmarcar dia
6. Ver calendario mensal de colaborador
0. Sair (guarda automaticamente)
Exemplo de Uso

Adicionar colaborador: Diogo Bilreiro
Marcar férias: 2025/08/15 - Tipo F
Ver calendário: Agosto 2025

Exemplo de Calendário
Calendario de Diogo Bilreiro - Agosto 2025
Dom Seg Ter Qua Qui Sex Sab
                      1  -
 -   4   5   6   7   8  -
 -  11  12  13  14  F  -
 -  18  19  20  21  22 -
 -  25  26  27  28  29 -

Legenda: F=ferias, X=falta, -=fim-de-semana
##🔒 Segurança
Os nomes dos colaboradores são encriptados usando Cifra de César (deslocamento de 3 caracteres) antes de serem gravados no ficheiro dados_rh.txt.

#📋 Requisitos
Compilador C++ com suporte a C++11 ou superior
Sistema operativo: Windows, Linux ou macOS

#👨‍💻 Desenvolvimento
Linguagem: C++
Standard: C++11
Bibliotecas: Apenas STL (iostream, fstream, string, vector, sstream)

#📝 Notas Técnicas
Validação de anos bissextos implementada
Algoritmo de Zeller para cálculo do dia da semana
Persistência automática ao sair do programa
Tratamento de erros em operações de I/O

#🎓 Projeto Académico
Desenvolvido para a disciplina de Programação - Mini-Sistema de Gestão de RH com foco em:

Programação orientada a objetos
Modularização de código
Persistência de dados
Validações e tratamento de erros


Versão: 1.0
Autor: [Diogo Bilreiro]

Data: Novembro 2025



