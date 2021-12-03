#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

void task1(const string&);
void task2(const string&);

int main() {
    string path;
    fstream fileStream;
    char confirmChar('m');

    cout << "AoC, day 3.\n";
    do {
        cout << "Type path to input file with puzzles:\n";
        cin >> path;

        fileStream.open(path);
        if(fileStream.is_open())
        {
            fileStream.close();
            cout << "File successfully opened!\n";
            cout << "First task result - ";
            task1(path);

            cout << "Second task result - ";
            task2(path);

            break;
        }
        else
        {
            fileStream.close();
            cout << "Wrong path to file. Not opened. Try again? y/n - ";
            cin >> confirmChar;
            if(confirmChar == 'y' || confirmChar == 'Y') confirmChar = 'm';
        }
    }while(confirmChar == 'm');
}

struct Bits
{
    int zero;
    int one;
};
void task1(const string &path)
{
    Bits bitsCount[12] = {0};
    fstream stream;

    stream.open(path);
    string currentBinary;
    int k = 1;
    while(!stream.eof())
    {
        getline(stream, currentBinary);
        for(int i = 0; i < 12; i++)
        {
            int currentInt = (int)currentBinary[i] - 48;
            if(currentInt == 1) bitsCount[i].one++;
            else bitsCount[i].zero++;
        }
    }
    stream.close();

    string gammaRateBin, epsRateBin;
    gammaRateBin.resize(12); epsRateBin.resize(12);

    for(int i = 0; i < 12; i++)
        if(bitsCount[i].one > bitsCount[i].zero)
        {
            gammaRateBin[i] = '1';
            epsRateBin[i] = '0';
        }
        else
        {
            gammaRateBin[i] = '0';
            epsRateBin[i] = '1';
        }

    unsigned long gammaRate = bitset<64>(gammaRateBin).to_ulong(), epsRate = bitset<64>(epsRateBin).to_ulong();

    cout << gammaRate * epsRate << '\n';
}

void task2(const string &path)
{
    fstream stream;
    vector<string> binNumbers;
    stream.open(path);

    int k = 1;
    binNumbers.resize(k);
    while(!stream.eof())
    {
        binNumbers.resize(k);
        getline(stream, binNumbers[k - 1]);
        k++;
    }
    stream.close();

    vector<string> ogRate;
    ogRate.resize(binNumbers.size());
    int o = 0;
    for(const string& f : binNumbers)
    {
        ogRate[o] = f;
        o++;
    }

    int m = 0;
    while(ogRate.size() != 1)
    {
        int zero(0), one(0);
        for(string j : ogRate)
        {
                int currentInt = (int)j[m] - 48;
                if(currentInt == 1) one++;
                else zero++;
        }

        char bitCriteria;
        if(one >= zero)
        {
            bitCriteria = '1';
        }
        else
        {
            bitCriteria = '0';
        }

        bool isAllAtCriteria = false;
        int i = 0;
        while(!isAllAtCriteria)
        {
            if(ogRate[i].at(m) != bitCriteria)
            {
                ogRate.erase(ogRate.begin() + i);
                i = 0;
                isAllAtCriteria = true;

                for(string k : ogRate)
                    if(k.at(m) != bitCriteria)
                    {
                        isAllAtCriteria = false;
                        break;
                    }
            }
            else i++;
        }
        m++;
    }

    vector<string> co2Rate;
    co2Rate.resize(binNumbers.size());
    int o1 = 0;
    for(const string& f : binNumbers)
    {
        co2Rate[o1] = f;
        o1++;
    }
    int l = 0;
    while(co2Rate.size() != 1)
    {
        int zero(0), one(0);
        for(string j : co2Rate)
        {
            int currentInt = (int)j[l] - 48;
            if(currentInt == 1) one++;
            else zero++;
        }

        char bitCriteria;
        if(zero <= one)
        {
            bitCriteria = '0';
        }
        else
        {
            bitCriteria = '1';
        }

        bool isAllAtCriteria = false;
        int i = 0;
        while(!isAllAtCriteria)
        {
            if(co2Rate[i].at(l) != bitCriteria)
            {
                co2Rate.erase(co2Rate.begin() + i);
                i = 0;
                isAllAtCriteria = true;

                for(string u : co2Rate)
                    if(u.at(l) != bitCriteria)
                        isAllAtCriteria = false;
            }
            else i++;
        }

        l++;
    }

    unsigned long ogRateInt = bitset<64>(ogRate[0]).to_ulong(), co2RateInt = bitset<64>(co2Rate[0]).to_ulong();

    cout << ogRateInt * co2RateInt;
}