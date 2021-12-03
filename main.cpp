#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

void task1(const string&);
void task2(const string&);
struct Bits
{
    int zero;
    int one;
};

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
            cout << "First task data:\n";
            task1(path);

            cout << "Second task data:\n";
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

void task1(const string &path)
{
    fstream stream;

    vector<string> inputNums;
    int inputNumsSize = 0;
    stream.open(path);
    while(!stream.eof())
    {
        inputNumsSize++;
        inputNums.resize(inputNumsSize);
        getline(stream, inputNums[inputNumsSize - 1]);
    }
    stream.close();

    const size_t binLength = inputNums[0].size();
    vector<Bits> bitsCount; bitsCount.resize(binLength);

    for(string num : inputNums)
        for(int idx = 0; idx < binLength; idx++)
        {
            int currentBit = (int)num[idx] - 48;
            if(currentBit == 1) bitsCount[idx].one++;
            else bitsCount[idx].zero++;
        }

    string gammaRateBin, epsRateBin;
    gammaRateBin.resize(binLength); epsRateBin.resize(binLength);

    for(int idx = 0; idx < binLength; idx++)
        if(bitsCount[idx].one > bitsCount[idx].zero)
        {
            gammaRateBin[idx] = '1';
            epsRateBin[idx] = '0';
        }
        else
        {
            gammaRateBin[idx] = '0';
            epsRateBin[idx] = '1';
        }

    unsigned long gammaRate, epsRate;
    gammaRate = bitset<64>(gammaRateBin).to_ulong();
    epsRate = bitset<64>(epsRateBin).to_ulong();

    cout << "Gamma rate - " << gammaRate << '\n';
    cout << "Epsilon rate - " << epsRate << '\n';
    cout << "Result - " << gammaRate * epsRate << '\n';
}

void task2(const string &path)
{
    fstream stream;
    vector<string> inputNums;
    int inputNumsSize = 0;

    stream.open(path);
    while(!stream.eof())
    {
        inputNumsSize++;
        inputNums.resize(inputNumsSize);
        getline(stream, inputNums[inputNumsSize - 1]);
    }
    stream.close();

    const size_t binLength = inputNums[0].size();

    vector<string> ogRateBin, co2RateBin;
    ogRateBin.resize(inputNumsSize);
    co2RateBin.resize(inputNumsSize);

    for(int idx = 0; idx < inputNumsSize; idx++)
    {
        ogRateBin[idx] = inputNums[idx];
        co2RateBin[idx] = inputNums[idx];
    }

    int position = 0;
    while(position != binLength)
    {
        int zeroBitCount[2] = {}, oneBitCount[2] = {};
        for(string ogRateBinStr : ogRateBin)
            if(ogRateBinStr[position] == '1') oneBitCount[0]++;
            else zeroBitCount[0]++;
        for(string co2RateBinStr : co2RateBin)
            if(co2RateBinStr[position] == '1') oneBitCount[1]++;
            else zeroBitCount[1]++;

        char currentOgRateBitCriteria, currentCo2RateBitCriteria;
        currentOgRateBitCriteria = oneBitCount[0] >= zeroBitCount[0] ? '1' : '0';
        currentCo2RateBitCriteria = oneBitCount[1] >= zeroBitCount[1] ? '0' : '1';

        bool isAllStrUnderCriteria = false;
        int ogRateIdx = 0;
        int co2RateIdx = 0;

        while(!isAllStrUnderCriteria)
        {
            if(ogRateBin[ogRateIdx][position] != currentOgRateBitCriteria && ogRateBin.size() != 1)
            {
                ogRateBin.erase(ogRateBin.begin() + ogRateIdx);
                isAllStrUnderCriteria = true;
                
                for(int idx = ogRateIdx; idx < ogRateBin.size(); idx++)
                    if(ogRateBin[idx][position] != currentOgRateBitCriteria)
                    {
                        ogRateIdx = idx == 0 ? 0 : idx;
                        isAllStrUnderCriteria = false;
                        break;
                    }
            }
            else ogRateIdx++;

            if(co2RateBin[co2RateIdx][position] != currentCo2RateBitCriteria && co2RateBin.size() != 1)
            {
                co2RateBin.erase(co2RateBin.begin() + co2RateIdx);
                isAllStrUnderCriteria = true;

                for(int idx = co2RateIdx; idx < co2RateBin.size(); idx++)
                    if(co2RateBin[idx][position] != currentCo2RateBitCriteria)
                    {
                        co2RateIdx = idx == 0 ? 0 : idx;
                        isAllStrUnderCriteria = false;
                        break;
                    }
            }
            else co2RateIdx++;
        }
        position++;
    }

    unsigned long ogRateInt, co2RateInt;
    ogRateInt = bitset<64>(ogRateBin[0]).to_ulong();
    co2RateInt = bitset<64>(co2RateBin[0]).to_ulong();

    cout << "Oxygen gen rate - " << ogRateInt << '\n';
    cout << "CO2 scrubber rate - " << co2RateInt << '\n';
    cout << "Result - " << ogRateInt * co2RateInt << '\n';
}