// Вариант 25 Банковский кредит Сортировка по процентам Копирование из deque в list
#include <iostream>
#include <fstream>
#include <deque>
#include <list>
#include <algorithm>
#include <string>

class Credit {

    std::string name;
    double amount;
    std::string currency;
    double stake;

public:
    // Конструктор
    Credit(std::string n, double a, std::string c, double r)
            : name(n), amount(a), currency(c), stake(r) {}

    // Оператор вставки в поток (перегрузка)
    friend std::ostream& operator<<(std::ostream& os, const Credit& credit) {
        os << "Name: " << credit.name << "\n"
           << "Sum: " << credit.amount << "\n"
           << "Currency: " << credit.currency << "\n"
           << "Stake (% per year): " << credit.stake << "\n";
        return os;
    }
    // Операторы присваивания/копирования не нужны, так как объекты не содержат указателей и без этих операторов все нормально работает

    // Оператор сравнения для сортировки
    bool operator<(const Credit& other) const {
        return stake < other.stake;
    }
};

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    std::deque<Credit> creditsDeque;
    std::string name, currency;
    double amount, rate;

    // Чтение данных из файла
    while (std::getline(input, name)) {
        input >> amount;
        input.ignore();
        std::getline(input, currency);
        input >> rate;
        input.ignore();

        creditsDeque.emplace_back(name, amount, currency, rate);
    }

    // Вывод исходного контейнера
    output << "deque:\n";
    for (const auto& credit : creditsDeque) {
        output << credit << "\n";
    }

    // Сортировка deque по ставке
    std::sort(creditsDeque.begin(), creditsDeque.end());

    // Вывод отсортированного контейнера
    output << "\ndeque_sorted:\n";
    for (const auto& credit : creditsDeque) {
        output << credit << "\n";
    }

    // Копирование в list
    std::list<Credit> creditsList;
    std::copy(creditsDeque.begin(), creditsDeque.end(), std::back_inserter(creditsList));

    // Вывод скопированного контейнера
    output << "\nlist:\n";
    for (const auto& credit : creditsList) {
        output << credit << "\n";
    }

    input.close();
    output.close();

    return 0;
}
