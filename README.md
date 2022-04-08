# Contatos

Este é um projeto proposto na disciplina de **Estrutura de Dados 1** do [**Instituto de Informática**](https://inf.ufg.br/) da [**Universidade Federal de Goiás**](https://www.ufg.br/).

É um aplicativo de contatos que salva as informações **nome**, **telefone**, **email**. Também é possível buscar um contato.

Foi desenvolvido usando:
- Linguagem [`c`](https://en.wikipedia.org/wiki/C_(programming_language))
- Widget toolkit [`Gtk`](https://www.gtk.org/)
- Ferramenta [`Glade`](https://gitlab.gnome.org/GNOME/glade) para RAD

## Como compilar e executar?

Os requisitos são:
* [Git](https://git-scm.com/)
* [GNU Make](https://www.gnu.org/software/make/)
* Um Compilador para **C**
    * [GCC](https://gcc.gnu.org/) ou
    * [Clang](https://clang.llvm.org/) ou
    * [MinGW](https://www.mingw-w64.org/)
* [Gtk >= 3](https://www.gtk.org/docs/installations/)
* [Pgk-config](https://www.freedesktop.org/wiki/Software/pkg-config/)

### Instalação das ferramentas
* No **Windows**

Instale gerenciador de pacotes [Msys2](https://www.msys2.org/).

Instalando git, make, MinGW, Gtk
```powershell
> pacman -S git make mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk3
```

* No **Ubuntu, Debian, Mint, PopOS**...</br>

Execute o comando no Terminal
```bash
$ sudo apt update && sudo apt install git build-essential
```

* No **MacOS** </br>

Instale [Command Line Tools](https://developer.apple.com/download/all/) ou [Xcode](https://developer.apple.com/download/all/)

Instale gerenciador de pacotes [HomeBrew](https://brew.sh/)
```zsh
$ brew install gtk+3
```
### Compilando e executando
Basta clonar o repositório e utilizar o comando make para compilar
```bash
$ git clone https://github.com/diogoborges14/contatos.git
$ cd contatos/
$ make
$ /contatos
```

## License
This project is licensed under the terms of the [MIT](https://choosealicense.com/licenses/mit/) license.