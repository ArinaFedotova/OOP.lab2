#ifndef SYSTEM_ERRORS_H
#define SYSTEM_ERRORS_H
#include <iostream>

class System_errors : public std::exception { // пишем свою ошибку наследование
private:
    std::string error_message; // само сообщение
public:
    System_errors(const std::string& message) : error_message{message} {} // конструктор записывающий сообщение это : делигирование инициализации присвоил
    const char* what() const noexcept {
        return error_message.c_str();  // сообщение о нашей ошибке
    }
};

#endif // SYSTEM_ERRORS_H
// System_errors(const std::string& message) -  частично параметризированный потому что не переадаем все атрибуты которые надо определить
// первый - возвр тип константнй
// второй - внутренние объекты константны

// фасад - удобный интерфейс для работы
// курьер - выполняеь то что тебе нужно привезти ( ты самостоятельно не едешь на склад)
// фасад - доп интерфейс
// - может перенагружать память
