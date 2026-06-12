#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

// Класс для хранения скобки и её позиции
class BracketInfo {
public:
    char bracket;
    int position;
    BracketInfo* next;
    BracketInfo(char br, int pos);
};

// Собственная реализация стека на основе односвязного списка
class Stack {
private:
    BracketInfo* top;
    int size;
    
public:
    Stack();
    ~Stack();
    void push(char bracket, int position);
    BracketInfo pop();
    BracketInfo peek();
    bool isEmpty();
    int getSize();
};

// Исключение: лишняя закрывающая скобка
class ExtraClosingException {
private:
    int position;
    char bracket;
public:
    ExtraClosingException(int pos, char br);
    std::string getMessage() const;
    int getPosition() const;
    char getBracket() const;
};

// Исключение: несоответствие типов скобок
class MismatchBracketException {
private:
    int position;
    char expected;
    char found;
public:
    MismatchBracketException(int pos, char exp, char fnd);
    std::string getMessage() const;
    int getPosition() const;
    char getExpected() const;
    char getFound() const;
};

// Исключение: не хватает закрывающей скобки
class MissingClosingException {
private:
    int position;
    char bracket;
public:
    MissingClosingException(int pos, char br);
    std::string getMessage() const;
    int getPosition() const;
    char getBracket() const;
};

// Исключение: в строке нет ни одной скобки
class NoBracketsException {
public:
    NoBracketsException();
    std::string getMessage() const;
};

// Исключение: недопустимый символ (не скобка и не пробел)
class InvalidCharacterException {
private:
    int position;
    char character;
public:
    InvalidCharacterException(int pos, char ch);
    std::string getMessage() const;
    int getPosition() const;
    char getCharacter() const;
};

// Основной класс проверки скобочной последовательности
class BracketChecker {
private:
    Stack stack;
    
    bool isOpening(char c);
    bool isClosing(char c);
    bool isMatching(char opening, char closing);
    bool isSpace(char c);
    bool isValidBracketOrSpace(char c);
    
public:
    BracketChecker();
    int checkSequence(const std::string& sequence);
    void printResult(const std::string& sequence);
};

#endif