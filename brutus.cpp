/**
 * Brutus: a brute-force Caesar decipherer.
 * Named, of course, for Marcus Junius Brutus, one of Caesar's assassins on the Ides of March.
 * @author Connor McDermid
 * @date 2024-03-12
 * Copyright 2024 Connor McDermid
 * This program is licensed under the MIT license. For full text, please see https://opensource.org/license/mit
 * or contact the author for a copy.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cxxopts.hpp> // cxxopts

using std::cout;
using std::endl;
using std::cerr;
using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;

/**
 * Given a ciphertext line and a key, attempt to decrypt the message.
 * @param line ciphertext
 * @param key key
 * @return the (hopefully) decrypted message
 */
string decipher(string& line, int key) {
    string plain = line;
    for (int i = 0; i < plain.size(); i++) {
        plain[i] = plain[i] - key;
        if (plain[i] < 65) {
            plain[i] += 26; // wrap it back around
        }
    }
    return plain;
}

/**
 * Print a string to stdout, or to a file.
 * @param out string to print
 * @param filename a file -- defaults to stdout
 */
void out(string& out, string filename="stdout") {
    if (filename == "stdout") {
        cout << out << endl;
        return;
    }
    ofstream output(filename, std::ios_base::app);
    output << out << endl;
    output.close();
}

/**
 * Print an int to stdout, or to a file
 * @param out int to print
 * @param filename a file -- defaults to stdout
 */
void out(int out, string filename="stdout") {
    if (filename == "stdout") {
        cout << out << endl;
        return;
    }
    ofstream output(filename, std::ios_base::app);
    output << out << endl;
    output.close();
}

/**
 * A hastily written program to decipher the Caesar cipher.
 * @param argc argument count
 * @param argv argument values
 * @return 0 on successful completion -- a positive number otherwise
 */
int main(int argc, char** argv) {
    //argument handling
    string outputfile = "stdout";
    string searchword;
    if (argc < 2 || argc == 4 || argc > 5) {
        cout << "Usage: brutus <cipherfile> [searchword] [-o outputfile]" << endl;
        exit(1);
    }
    if (argc == 5 && strcmp(argv[3], "-o") == 0) {
        outputfile = argv[4];
        searchword = argv[2];
    }
    if (argc == 3) {
        searchword = argv[2];
    }

    if (strcmp(argv[1], "-v") == 0) {
        cout << "Brutus: version 1.0" << endl;
        exit(3);
    }

    ifstream cipherfile;
    try {
        cipherfile.open(argv[1]);
    } catch (std::exception& e) {
        cout << "Could not open file!" << endl;
        cerr << e.what() << endl;
        exit(2);
    }

    // read from file
    string cipher;
    try {
        getline(cipherfile, cipher);
    }  catch (std::exception& e) {
        cout << "Could not read from file!" << endl;
        cerr << e.what() << endl;
        exit(5);
    }

    if (searchword.empty()) {
        for (int i = 0; i < 26; i++) {
            out(decipher(cipher, i).append(" "), outputfile);
            out(i, outputfile);
        }
    } else {
        string tmp;
        for (int i = 0; i < 26; i++) {
            tmp = decipher(cipher, i);
            if (tmp.find(searchword) != std::string::npos) { // if string contains search term
                // then that's the one we want
                out(tmp, outputfile);
                out(i, outputfile);
                break; // exit loop, we're done
            }
        }
    }

    try {
        cipherfile.close();
    } catch (std::exception& e) {
        cout << "Could not close file!" << endl;
        cerr << e.what() << endl;
        exit(4);
    }

    return 0;
}