#include <iostream>
#include <vector>

#define POWER 26
#define CONST 100000
using namespace std;


struct Entry {
    int position;
    int patternIndex;
};

struct Node {
    char value;
    int parent;
    bool isLeaf;
    
    int nextNode[POWER]; //указатель на вершину, в которую ведет ребро, если не ведет -1
    int transition[POWER]; // массив переходов
    
    int suffixLink; // суффиксная ссылка
    int suffixLinkLeafOnly; // сжатая суффиксная ссылка
    
    int patternLength; // длина шаблона
    vector<int> patternNumber; // номер шаблона
    
    Node(char _value);
};

/**
 * Разбивает текст на подстроки с разделителем `joker`.
 */
struct JokeredString {
    
    const char joker;
    
    /** Длина исходной строки */
    const size_t length;
    
    /**
     * Подстроки, полученные при раздечении текста по джокеру.
     * Пустые строки между подряд идущими джокерами не сохраняются.
     */
    vector<string> substrings;
    
    /** Позиции этих подстрок */
    vector<int> positions;
    
    /**
     * Разбивает текст на подстроки с разделителем `joker`.
     */
    JokeredString(const string &input, char _joker);
};

struct Bohr {
public:
    void push(const string &pattern, int patternIndex);
    
    vector<int> ahoKorasic(const string &text, JokeredString jokered);
    
    Bohr();
    
private:
    
    vector<Node> nodes;
    
    int getTransition(int index, char chr);
    
    int getSuffixLink(int index);
    
    int getSuffixLinkLeafOnly(int index);
    
};

int main() {
    string text;
    string pattern;
    char joker;
    
    cin >> text;
    cin >> pattern;
    cin >> joker;
    
    Bohr bohr;
    
    /** Разделяет паттерн на подстроки по джокеру */
    JokeredString jokered(pattern, joker);
    
    for (size_t i = 0; i < jokered.substrings.size(); i++) {
        string substring = jokered.substrings[i];
        bohr.push(substring, i + 1);
    }
    
    auto result = bohr.ahoKorasic(text, jokered);
    
    for (int i = 0; i < CONST; i++) {
        if (result[i] == jokered.positions.size())
            cout << i << endl;
    }
    
}

Node::Node(char _value) {
    for (int i = 0; i < POWER; i++) {
        nextNode[i] = -1;
        transition[i] = -1;
    }
    isLeaf = false;
    value = _value;
}


JokeredString::JokeredString(const string &input, char _joker) : joker(_joker), length(input.length()) {
    string substring;
    for (size_t i = 0; i < input.length(); i++) { // разбиение на подстроки без джокеров
        if (input[i] != joker) {
            substring += input[i];
            if ((input[i - 1] == joker) || (i == 0))
                positions.push_back(i + 1);
        }
        if (i == input.length() - 1 || input[i] == joker) {
            if ((i != 0 && input[i - 1] != joker) ||
                (i == input.length() - 1 && input[i] != joker)) {
                substrings.push_back(substring);
                substring.clear();
            }
        }
    }
}

int Bohr::getSuffixLinkLeafOnly(int index) {
    Node &vertex = nodes[index];
    if (vertex.suffixLinkLeafOnly == 0) {
        int suffix_link = getSuffixLink(index);
        if (nodes[suffix_link].isLeaf) {
            vertex.suffixLinkLeafOnly = suffix_link;
        } else {
            if (suffix_link != 0)
                vertex.suffixLinkLeafOnly = getSuffixLinkLeafOnly(suffix_link);
            else vertex.suffixLinkLeafOnly = 0;
        }
    }
    return vertex.suffixLinkLeafOnly;
}

int Bohr::getSuffixLink(int index) {
    Node &vertex = nodes[index];
    if (vertex.suffixLink == 0) {
        if (vertex.parent == 0 || index == 0) vertex.suffixLink = 0;
        else {
            int suffix_link = getSuffixLink(vertex.parent); // Рекурсия
            vertex.suffixLink = getTransition(suffix_link, vertex.value);
        }
    }
    return vertex.suffixLink;
}

/**
 * Переход присутствует                                     -> Берем переход.
 * Переход отсутствует + Следующая присутствует             -> Следующая
 * Переход отсутствует + Следующая отсутствует + Корень     -> 0
 * Переход отсутствует + Следующая отсутствует + НЕ Корень  -> Рекурсия по суффиксной ссылке
 */
int Bohr::getTransition(int index, char chr) { //вычисление перехода
    int char_number = chr - 'A';
    Node &vertex = nodes[index];
    if (vertex.transition[char_number] != -1)
        return vertex.transition[char_number];
    if (vertex.nextNode[char_number] != -1)
        return vertex.transition[char_number] = vertex.nextNode[char_number];
    if (index != 0)
        return vertex.transition[char_number] = getTransition(getSuffixLink(index), chr);
    return vertex.transition[char_number] = 0;
}

Bohr::Bohr() {
    Node root('#');
    {// Инициализация
        root.isLeaf = false;
        root.suffixLink = -1;
        root.suffixLinkLeafOnly = -1;
        root.parent = 0;
    }
    nodes.push_back(root);
}

void Bohr::push(const string &pattern, int patternIndex) {
    int index = 0;
    for (char letter : pattern) {
        int char_number = letter - 'A';
        if (nodes[index].nextNode[char_number] == -1) {
            Node symb(letter);
            symb.suffixLink = 0;
            symb.suffixLinkLeafOnly = 0;
            symb.parent = index;
            
            nodes.push_back(symb);
            nodes[index].nextNode[char_number] = nodes.size() - 1;
        }
        index = nodes[index].nextNode[char_number];
    }
    nodes[index].isLeaf = true;
    nodes[index].patternLength = pattern.length();
    nodes[index].patternNumber.push_back(patternIndex);
}

vector<int> Bohr::ahoKorasic(const string &text, JokeredString jokered) {
    vector<int> result(CONST);
    int index = 0; // считаем Ахо-Корасик
    for (size_t i = 0; i < text.length(); i++) {
        index = getTransition(index, text[i]);
        for (int j = index; j > 0; j = getSuffixLinkLeafOnly(j)) {
            if (nodes[j].isLeaf) {
                for (size_t r = 0; r < nodes[j].patternNumber.size(); r++) {
                    int patternPosition = i - nodes[j].patternLength + 2;
                    int patternNumber = nodes[j].patternNumber[r];
                    int substringPosition = jokered.positions[patternNumber - 1];
                    if ((patternNumber + jokered.length - substringPosition <= text.length()) &&
                        (patternPosition - substringPosition + 1 > 0))
                        result[patternPosition - substringPosition + 1]++;
                }
            }
        }
    }
    return result;
}



