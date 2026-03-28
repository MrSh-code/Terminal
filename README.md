# Terminal
## Сборка и запуск

Для компиляции программы используйте любой компилятор с поддержкой C++11 (например, g++, clang или MinGW).

### Команда компиляции (g++)

```bash
g++ -std=c++11 -o terminal main.cpp Entry.cpp Directory.cpp SingleLineFile.cpp MultiLineFile.cpp PostponedFile.cpp Terminal.cpp
```

### Запуск

```bash
./terminal
```

## Список команд

- `help` – вывод списка команд
- `exit` – завершение работы
- `ls` – показ содержимого текущей директории
- `cd <имя>` – переход в поддиректорию (поддерживается `..`)
- `cat <файл>` – вывод содержимого файла
- `touch <файл>` – создание нового файла (тип определится при первом редактировании)
- `mkdir <имя>` – создание новой директории
- `rm <имя>` – скрытие файла или директории
- `restore <имя>` – восстановление скрытого элемента
- `mv <старое_имя> <новое_имя>` – переименование
- `edit <файл>` – редактирование файла; для новых файлов предлагает выбрать тип


## Определение архитектуры и авторитативных решений

### Иерархия классов
-`Entry` – базовый класс для всех элементов ФС.

-`Directory` – директория, наследует Entry.

-`SingleLineFile` – однострочный файл.

-`MultiLineFile` – многострочный файл.

-`PostponedFile` – файл с отложенным определением типа (прокси).

### Ключевые полиморфные методы в Entry
Все они виртуальные и имеют реализации по умолчанию:

-`std::string getName() const`

-`void setName(const std::string&)`

-`bool isHidden() const`

-`void setHidden(bool)`

-`void printContent() const` – для файлов выводит содержимое

-`void edit()` – редактирование содержимого

-`void list() const` – для директорий выводит детей, для остальных ничего

-`bool isDirectory() const` – возвращает true только для Directory

-`Directory* getDirectory(const std::string& name) const` – возвращает поддиректорию по имени (если текущий объект – директория и среди детей есть такая поддиректория), иначе nullptr

### Где хранится скрытость
В `Entry` поле `bool hidden`. `rm` и `restore` просто меняют его.

Фильтрация при `ls` выполняется в `Directory::list()`: выводим только детей, у которых `hidden == false`.

### Поиск сущности
`Directory::findChild(const std::string& name) const` возвращает `std::shared_ptr<Entry>` (или `nullptr`). Ищет по имени среди всех детей (включая скрытые). Используется командами `mv`, `rm`, `restore`, `cat`, `edit` для получения объекта.

### Навигация без проверки типов
`Terminal::cd` вызывает `currentDir->getDirectory(path)`.

`Directory::getDirectory(name)` ищет среди детей элемент с именем name, затем проверяет `child->isDirectory()`. Если да – возвращает `static_cast<Directory*>(child.get())` (или `dynamic_cast`, но мы можем использовать `child->asDirectory()` с полиморфным возвратом, но проще добавить `isDirectory()` и затем привести через `static_cast`, зная, что это безопасно).

### Текущий путь
`Terminal` хранит `std::shared_ptr<Directory> root` и `Directory* currentDir`.

При `cd ".."` проверяем `currentDir->getParent()` и обновляем, если не `nullptr`.

При `cd <name>` вызываем `currentDir->getDirectory(name)`.

### Отложенное определение типа
`touch` создаёт `PostponedFile`.

`PostponedFile` имеет поле `std::shared_ptr<Entry> actualFile`, изначально `nullptr`.

Все методы `PostponedFile` делегируют `actualFile`, если он есть, иначе выполняют логику по умолчанию.

`PostponedFile::edit()`: если `actualFile` нет, предлагает пользователю выбрать тип (1 – однострочный, 2 – многострочный), запрашивает содержимое, создаёт соответствующий файл и сохраняет его в `actualFile`. При последующих вызовах `edit` делегирует `actualFile->edit()`.

  
