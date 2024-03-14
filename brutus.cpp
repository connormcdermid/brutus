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
   cxxopts::Options options("Brutus", "A simple monoalphabetic cipher brute force program.");
   options.add_options()
           ("v,version", "Print program version")
           ("o,out", "specify an output file", cxxopts::value<std::string>()->default_value(""))
           ("c,caesar", "Caesar cipher", cxxopts::value<bool>()->default_value("true"))
           ("k, key", "Specify a specific key(s) to try", cxxopts::value<std::vector<std::string>>())
           ("ciphertext", "the ciphertext file to operate on", cxxopts::value<std::string>())
           ;
   auto result = options.parse(argc, argv);

   if (result["version"].as<bool>()) {
       
   }

    return 0;
}