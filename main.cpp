#include <iostream>
#include <NTL/vec_GF2.h>
#include <NTL/GF2XFactoring.h>
using namespace std;
using namespace NTL;


long get_linear_complexity(const vec_GF2& s) {
    if (IsZero(s)) return 0;
    GF2X f;
    MinPolySeq(f, s, s.length()); // nájde minimálny polynóm postupnosti
    return deg(f);    // vráti stupeň polynómu ako lineárnu zložitosť
}

void introduction() {
    cout << "Určenie sférickej zložitosti rádu 1 postupnosti mod 2" << endl;
    cout << "Autor: Boris Pekarčík, Rudolf Tisoň" << endl;
    cout << endl << "Vstup je postupnosť; musí obsahovať iba znaky 0/1" << endl;
    cout << "(napr. 0111001)" << endl << endl;
}

vec_GF2 input_sequence() {
    string str;

    cout << "Zadajte postupnosť: ";
    cin >> str;

    if (str.empty()) {
        cout << endl << "Postupnosť nemôže byť prázdna" << endl;
        return {};
    }

    vec_GF2 sequence;
    sequence.SetLength(static_cast<long>(str.size()));
    for (int i = 0; i < str.size(); i++) {
        const char c = str[i];
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
    introduction();

    const vec_GF2 sequence = input_sequence();
    if (sequence.length() == 0) {
        return 1;
    }

    return 0;
}