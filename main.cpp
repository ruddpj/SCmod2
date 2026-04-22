#include <iostream>
#include <vector>
#include <NTL/vec_GF2.h>
#include <NTL/GF2X.h>
using namespace std;
using namespace NTL;

long berlekamp_massey(const vec_GF2& s) {
    const long n = s.length();
    if (n == 0) return 0;

    // C - aktuálny connection polynomial, B - predchádzajúci
    vector<long> C(n + 1, 0), B(n + 1, 0);
    C[0] = 1;
    B[0] = 1;

    long L = 0;   // aktuálna lineárna zložitosť
    long m = 1;   // počet krokov od poslednej zmeny
    long b = 1;   // hodnota predchádzajúceho diskrepaničného bitu (vždy 1 v GF(2))

    for (long i = 0; i < n; i++) {
        // Výpočet diskrepancie d
        long d = conv<long>(s[i]);
        for (long j = 1; j <= L; j++) {
            d ^= (C[j] & conv<long>(s[i - j]));
        }

        if (d == 0) {
            // Žiadna aktualizácia potrebná
            m++;
        } else if (2 * L <= i) {
            // Aktualizácia C a L
            const vector<long> T = C;
            for (long j = m; j <= n; j++) {
                C[j] ^= (b & B[j - m]);
            }
            L = i + 1 - L;
            B = T;
            b = d;  // v GF(2) je d vždy 1 keď nenulové
            m = 1;
        } else {
            // Aktualizácia C bez zmeny L
            for (long j = m; j <= n; j++) {
                C[j] ^= (b & B[j - m]);
            }
            m++;
        }
    }

    return L;
}

vec_GF2 input_sequence(const string &str) {
    vec_GF2 sequence;
    const long length = static_cast<long>(str.size());
    sequence.SetLength(length);

    for (int i = 0; i < length; i++) {
        const char c = str[i];
        const int x = c - '0';

        if (x != 0 && x != 1) {
            cout << endl << "ERROR: Postupnosť obsahuje nepovolene znaky." << endl;
            cout << "Povolene znaky: 0, 1" << endl;
            return {};
        }

        sequence[i] = x;
    }

    return sequence;
}

int main() {
    cout << "Urcenie sferickej zlozitosti radu 1 postupnosti mod 2" << endl;
    cout << "   Autor: Boris Pekarcík, Rudolf Tison" << endl << endl;

    cout << "Princip fungovania:" << endl;
    cout << "   1. Vypocet linearnej zlozitosti LC zadanej postupnosti S pomocou Berlekamp-Massey algoritmu." << endl;
    cout << "   2. Vypocet linearnej zlozitosti LC_i postupnosti S_i, kde S_i = S a i-ty prvok S_i(i) = S(i) + 1," << endl;
    cout << "       i patri {0, 1, ..., n - 1}, n je dlzka zadanej postupnosti." << endl;
    cout << "   3. Vypocet sferickej zlozitosti SC postupnosti S, kde SC(S) = min{LC, LC_0, LC_1, ..., LC_(n-1)}" << endl;

    cout << endl << "Vstup je postupnost; musi obsahovat iba znaky 0/1 (napr. 0111001)." << endl;

    while (true) {
        string str;
        cout << endl << "Zadajte postupnost (alebo \'q\' ak chcete skoncit): ";
        cin >> str;

        if (str == "q") break;

        if (str.empty()) {
            cout << endl << "ERROR: Postupnost nemoze byt prazdna." << endl;
            return 1;
        }

        vec_GF2 sequence = input_sequence(str);

        long min_complexity = berlekamp_massey(sequence); // Výpočet lineárnej zložitosti pôvodnej postupnosti
        cout << "   Povodna postupnost: LC(S) = " << min_complexity << endl << endl;
        cout << "   Vypocet postupnosti LC(S_i), pre i: {0, 1, ..., n - 1}" << endl ;

        for (int i = 0; i < sequence.length(); i++) {   // Výpočet pre postupnosti s_i = !s_i
            sequence[i] = 1 - sequence[i];
            long complexity = berlekamp_massey(sequence);

            cout << "   LC(S_" << i << ") = " << complexity << endl;

            if (complexity < min_complexity) {      // Porovnanie s najmenšou aktuálnou zložitosťou
                min_complexity = complexity;
            }

            sequence[i] = 1 - sequence[i];
        }

        cout << endl << "   Sfericka zlozitost SC(S) = " << min_complexity << endl;
    }

    return 0;
}