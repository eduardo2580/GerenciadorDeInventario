# Inventory Management System (Educational License)

**© 2025 Eduardo Souza Rodrigues - Licensed for Educational Use Only**  
*Protected under Brazilian Law 9,610/98 - Strictly Non-Commercial Academic Use*

[![License: Restricted Educational](https://img.shields.io/badge/License-Restricted_Educational-red.svg)](LICENSE)
[![Brazilian Law Compliance](https://img.shields.io/badge/Compliance-Brazilian_Law_9.610/98-blue)](https://www.planalto.gov.br/ccivil_03/leis/l9610.htm)

## 🔐 Key Restrictions (Full License in [LICENSE](LICENSE) file)
- **Forbidden**: Commercial use, AI training, blockchain, public deployments
- **Mandatory**: Copyright notice & [original repo link](https://github.com/eduardo2580/GerenciadorDeInventario)
- **Requires**: Content protection measures in derivative educational materials
- **Enforcement**: Civil/criminal penalties for violations (Brazilian jurisdiction)

## 📋 Project Overview
Command-line inventory system for academic C programming studies. Manages product data with CRUD operations and binary file storage.

```
Project Structure
├── .gitignore          - Version control exclusions
├── LICENSE             - Full legal terms (READ REQUIRED)
├── gerenciador.*       - Code::Blocks project files
├── inventario.bin      - Binary inventory database
└── main.c              - Core application logic
```

## 🛠️ Installation (Academic Use Only)
```bash
# Clone with mandatory attribution
git clone https://github.com/eduardo2580/GerenciadorDeInventario.git
cd GerenciadorDeInventario

# Compile with GCC
gcc main.c -o inventory
```

## 🧩 Features
```c
typedef struct {
    int id;                     // Unique identifier
    char nome[100];             // Product name
    int quantidade;             // Stock quantity
    float preco;                // Unit price
    char dataDeValidade[11];    // Expiry date (dd/mm/yyyy)
    char categoria[50];         // Product category
} Item;
```
- Dynamic memory management (`realloc`)
- Binary file I/O (`fwrite/fread`)
- Input validation loops
- Tabular data display

## ⚠️ Compliance Requirements
All educational uses must:
1. Display permanent header:  
   `"© Eduardo Souza Rodrigues - Licensed for Educational Use Only"`
2. Implement access controls:
   ```
   - Disable file downloads
   - Prevent code copying
   - Restrict to read-only classroom access
   ```
3. Maintain LICENSE file integrity

## 📜 License Amendments Alert
This restrictive license may change without notice:
1. Check `LICENSE` before each use
2. Changes effective immediately
3. Continued use = acceptance of new terms

## 📍 Jurisdictional Notice
```legal
All disputes will be resolved under:
- Governing Law: Brazil (Law 9,610/98)
- Exclusive Forum: São Paulo/SP Courts
- Penalties: Up to R$500,000 + criminal charges
```

**By using this repository, you acknowledge understanding and acceptance of these strict educational use terms.**  
*Last License Update: 2025-03-01 - Verify LICENSE file for current version*
```
