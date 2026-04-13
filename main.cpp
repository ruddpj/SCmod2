#include <iostream>
#include <vector>
#include <NTL/vec_GF2.h>
#include <NTL/GF2X.h>
using namespace std;
using namespace NTL;

long get_linear_complexity(const vec_GF2& s) {
    const long n = s.length();
    if (n == 0) return 0;

    const GF2X f = MinPolySeq(s, n / 2);
    return deg(f);
}

vec_GF2 input_sequence(const string &str) {
    vec_GF2 sequence;
    const long length = static_cast<long>(str.size());
    sequence.SetLength(length * 2);

    for (int i = 0; i < length * 2; i++) {
        const char c = str[i % length];
        const int x = c - '0';

        if (x != 0 && x != 1) {
            cout << endl << "Postupnosť obsahuje nepovolené znaky" << endl;
            cout << "Povolené znaky: 0, 1" << endl;
            return {};
        }

        sequence[i] = x;
    }

    return sequence;
}

int main() {
    cout << "Určenie sférickej zložitosti rádu 1 postupnosti mod 2" << endl;
    cout << "Autor: Boris Pekarčík, Rudolf Tisoň" << endl;
    cout << endl << "Vstup je postupnosť; musí obsahovať iba znaky 0/1 a byť celá perióda bez predperiódy." << endl;
    cout << "(napr. 0111001)" << endl << endl;

    while (true) {
        string str;
        cout << "Zadajte postupnosť (alebo \'q\' ak chcete skončiť): ";
        cin >> str;

        if (str == "q") break;

        if (str.empty()) {
            cout << endl << "Postupnosť nemôže byť prázdna" << endl;
            return 1;
        }

        vec_GF2 sequence = input_sequence(str);

        long min_complexity = get_linear_complexity(sequence); // Výpočet lineárnej zložitosti pôvodnej postupnosti
        for (int i = 0; i < sequence.length(); i++) {   // Výpočet pre postupnosti s_i = !s_i
            sequence[i] = 1 - sequence[i];
            long complexity = get_linear_complexity(sequence);

            if (complexity < min_complexity) {      // Porovnanie s najmenšou aktuálnou zložitosťou
                min_complexity = complexity;
            }

            sequence[i] = 1 - sequence[i];
        }

        cout << "Sférická zložitosť LC(s) = " << min_complexity << endl << endl;
    }

    return 0;
}