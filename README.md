# Cartas
_Cartas_ is a **Message Management System** developed as part of the course "[Programación I](https://secretaria.uvigo.gal/docnet-nuevo/guia_docent/index.php?centre=305&ensenyament=V05G301V01&assignatura=V05G301V01105&any_academic=2019_20)" in the Telecommunications Engineering Degree at the Universidad de Vigo (2019 - 2020).

## About The Project
This project simulates a management system for messaging, where users can send, receive, and organize messages. The system integrates fundamental programming concepts such as dynamic memory management, file handling, and modular design, which were key learning objectives of the course.

The project features:
- A system to create and remove users.
- A messaging system for sending, receiving and deleting messages.
- Logging system for all actions.
- Text-based output.

## How To Run
### Compilation
Make sure you have the [GCC](https://gcc.gnu.org) and [Makefile](https://www.gnu.org/software/make/) tools installed on your system. Then compile the project with:
```bash
make -C src
```
This command will generate the executable file inside the `src/` directory.

### Execution
Once compiled, you can run the system with:
```bash
./src/letters
```
Alternatively, you can download and run the precompiled version from the [releases page](https://github.com/Pirito10/Cartas-PI-UVigo/releases/tag/1.0).

## About The Code
The original specification document for this project was lost, so the only way to properly understand the system and how it works is by reading the ["Memoria"](docs/Memoria.pdf) document and inspecting the code directly.
