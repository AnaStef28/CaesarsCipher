#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void read_freq(float* letterFreq) {
    ifstream file("distribution.txt");
    string line;

    int i = 0;
    while (getline(file, line)) { 
        letterFreq[i] = atof(line.c_str()); 
        i++;
    }

    file.close();
}

void histogram(float* freqInCode, char text[]) {

    int lens = strlen(text);
    for (int i = 0; i < lens; i++) {
        if (text[i] >= 'a' && text[i] <= 'z')
            freqInCode[text[i] - 'a']++;
        else if (text[i] >= 'A' && text[i] <= 'Z')
            freqInCode[text[i] - 'A']++;
    }



}

float chiSquaredDistance(float* letterFreq, float* freqInCode) {
    float distance = 0;
    for (int i = 0; i < 26; i++) {
        distance += (((freqInCode[i] - letterFreq[i]) * (freqInCode[i] - letterFreq[i])) / letterFreq[i]);
    }
    return distance;
}

void permute(float* freqInCode) {

    float aux = freqInCode[0];
    for (int i = 0; i < 25; i++) {
        freqInCode[i] = freqInCode[i + 1];
    }
    freqInCode[25] = aux;

}

int offset(float* letterFreq, float* freqInCode) {

    int os = 0; //the offset
    int rez = 0; // the final result
    float minDist = 1000000000000;
    float dist = 0;

    while (os<25){
    
        dist = chiSquaredDistance(letterFreq, freqInCode);
        if (dist < minDist) {
            minDist = dist;
            rez = os;
        }
        permute(freqInCode);
        os++;
    }

    return rez;
}

void breakingCipher(float* letterFreq, float* freqInCode, char text[]) {
    read_freq(letterFreq);
    histogram(freqInCode, text);
    float os=offset(letterFreq, freqInCode);

    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
                text[i] = 'a' +int(text[i] - 'a' +(26 - os))%26;
        }
        else if (text[i] > 'A' && text[i] < 'Z') {
                text[i] = 'A' + int(text[i] - 'A' +(26- os))%26;
        }
    }

}

void menu() {

    cout << "Please input your coded message: \n";
    float freqInCode[26] = { 0 };
    float letterFreq[26];
    char text[1000];
    fgets(text, 1000, stdin);
    breakingCipher(letterFreq, freqInCode, text);
    cout << text;
}

int main() {
    
    menu();
    return 0;
}
