#include "task.h"

// ==== Реализация BracketInfo ====
BracketInfo::BracketInfo(char br, int pos) : bracket(br), position(pos), next(nullptr) {}

// ==== Реализация Stack ====
Stack::Stack() : top(nullptr), size(0) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(char bracket, int position) {
    BracketInfo* newNode = new BracketInfo(bracket, position);
    newNode->next = top;
    top = newNode;
    size++;
}

BracketInfo Stack::pop() {
    if (isEmpty()) {
        throw "Empty stack";
    }
    BracketInfo* temp = top;
    BracketInfo result = *top;
    top = top->next;
    delete temp;
    size--;
    return result;
}

BracketInfo Stack::peek() {
    if (isEmpty()) {
        throw "Empty stack";
    }
    return *top;
}

bool Stack::isEmpty() {
    return top == nullptr;
}

int Stack::getSize() {
    return size;
}

// ==== Реализация исключений ====
// ExtraClosingException
ExtraClosingException::ExtraClosingException(int pos, char br) : position(pos), bracket(br) {}
std::string ExtraClosingException::getMessage() const {
    return "Ошибка на позиции " + std::to_string(position) + ": лишняя закрывающая скобка '" + bracket + "'";
}
int ExtraClosingException::getPosition() const { return position; }
char ExtraClosingException::getBracket() const { return bracket; }

// MismatchBracketException
MismatchBracketException::MismatchBracketException(int pos, char exp, char fnd) 
    : position(pos), expected(exp), found(fnd) {}
std::string MismatchBracketException::getMessage() const {
    return "Ошибка на позиции " + std::to_string(position) + ": ожидалась закрывающая скобка для '" + expected + "', но найдена '" + found + "'";
}
int MismatchBracketException::getPosition() const { return position; }
char MismatchBracketException::getExpected() const { return expected; }
char MismatchBracketException::getFound() const { return found; }

// MissingClosingException
MissingClosingException::MissingClosingException(int pos, char br) : position(pos), bracket(br) {}
std::string MissingClosingException::getMessage() const {
    return "Ошибка на позиции " + std::to_string(position) + ": не хватает закрывающей скобки для '" + bracket + "'";
}
int MissingClosingException::getPosition() const { return position; }
char MissingClosingException::getBracket() const { return bracket; }

// NoBracketsException
NoBracketsException::NoBracketsException() {}
std::string NoBracketsException::getMessage() const {
    return "В строке нет ни одной скобки";
}

// InvalidCharacterException
InvalidCharacterException::InvalidCharacterException(int pos, char ch) : position(pos), character(ch) {}
std::string InvalidCharacterException::getMessage() const {
    return "Ошибка на позиции " + std::to_string(position) + ": недопустимый символ '" + character + "'. Разрешены только скобки ()[]{} и пробелы";
}
int InvalidCharacterException::getPosition() const { return position; }
char InvalidCharacterException::getCharacter() const { return character; }

// ==== Реализация BracketChecker ====
BracketChecker::BracketChecker() {}

bool BracketChecker::isOpening(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool BracketChecker::isClosing(char c) {
    return c == ')' || c == ']' || c == '}';
}

bool BracketChecker::isMatching(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool BracketChecker::isSpace(char c) {
    return c == ' ';
}

bool BracketChecker::isValidBracketOrSpace(char c) {
    return isOpening(c) || isClosing(c) || isSpace(c);
}

int BracketChecker::checkSequence(const std::string& sequence) {
    // Очищаем стек
    while (!stack.isEmpty()) {
        stack.pop();
    }
    
    bool hasBracket = false;  // флаг, были ли скобки
    
    for (int i = 0; i < sequence.length(); i++) {
        char current = sequence[i];
        int pos = i + 1;  // позиция с 1
        
        // Проверка на допустимые символы (только скобки и пробелы)
        if (!isValidBracketOrSpace(current)) {
            throw InvalidCharacterException(pos, current);
        }
        
        // Пробелы просто пропускаем
        if (isSpace(current)) {
            continue;
        }
        
        hasBracket = true;  // нашли скобку
        
        if (isOpening(current)) {
            stack.push(current, pos);
        }
        else if (isClosing(current)) {
            if (stack.isEmpty()) {
                throw ExtraClosingException(pos, current);
            }
            
            BracketInfo topInfo = stack.peek();
            if (!isMatching(topInfo.bracket, current)) {
                throw MismatchBracketException(pos, topInfo.bracket, current);
            }
            
            stack.pop();
        }
    }
    
    // Если скобок не было вообще - ошибка
    if (!hasBracket) {
        throw NoBracketsException();
    }
    
    if (!stack.isEmpty()) {
        BracketInfo remaining = stack.peek();
        throw MissingClosingException(remaining.position, remaining.bracket);
    }
    
    return -1;
}

void BracketChecker::printResult(const std::string& sequence) {
    std::cout << "\nПроверка последовательности: \"" << sequence << "\"\n";
    std::cout << "----------------------------------------\n";
    
    try {
        int result = checkSequence(sequence);
        if (result == -1) {
            std::cout << "ПОСЛЕДОВАТЕЛЬНОСТЬ КОРРЕКТНА!\n";
        }
    }
    catch (const ExtraClosingException& e) {
        std::cout << "ОШИБКА!\n";
        std::cout << "Позиция нарушения: " << e.getPosition() << "\n";
        std::cout << "Лишняя закрывающая скобка: '" << e.getBracket() << "'\n";
    }
    catch (const MismatchBracketException& e) {
        std::cout << "ОШИБКА!\n";
        std::cout << "Позиция нарушения: " << e.getPosition() << "\n";
        std::cout << "Ожидалась закрывающая скобка для '" << e.getExpected() 
                  << "', но найдена '" << e.getFound() << "'\n";
    }
    catch (const MissingClosingException& e) {
        std::cout << "ОШИБКА!\n";
        std::cout << "Позиция нарушения: " << e.getPosition() << "\n";
        std::cout << "Не хватает закрывающей скобки для '" << e.getBracket() << "'\n";
    }
    catch (const NoBracketsException& e) {
        std::cout << "ОШИБКА!\n";
        std::cout << "Позиция нарушения: нет (строка без скобок)\n";
        std::cout << e.getMessage() << "\n";
    }
    catch (const InvalidCharacterException& e) {
        std::cout << "ОШИБКА!\n";
        std::cout << "Позиция нарушения: " << e.getPosition() << "\n";
        std::cout << e.getMessage() << "\n";
    }
    std::cout << "----------------------------------------\n";
}