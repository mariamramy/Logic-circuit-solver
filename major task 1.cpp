#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int andd = 0, orr = 0, xorr = 0, nott = 0, nandd = 0, norr = 0;


// function to identify gates' unique integers
bool Operation(bool fnum, bool snum, int op)
{
    if (op == 2) //AND
    {
        andd++;
        return fnum && snum;
    }
    else if (op == 3) //OR
    {
        orr++;
        return fnum || snum;
    }
    else if (op == 4) //NOT
    {
        nott++;
        return !fnum;
    }
    else if (op == 5) //XOR
    {
        xorr++;
        return (fnum != 0) != (snum != 0);
    }
    else if (op == 6) //NOR
    {
        norr++;
        return !(fnum || snum);
    }
    else if (op == 7) //XNOR
    {
        return !(fnum != snum);
    }
    else if (op == 8) //NAND
    {
        nandd++;
        return !(fnum && snum);
    }

    return 0; //Default return value
}

// function to convert into numbers and inserts it into an array and modifies it accordingly
void tokenization(string word)
{
    bool first_value, second_value = false;
    int words[100] = { 0 };
    int temp[100] = { 0 };
    int string_index = 0;
    int word_index = 0;

    while (string_index < word.size())
    {
        if (word[string_index] == 'A')
        {
            words[word_index] = 2;
            string_index += 3;
        }
        else if (word[string_index] == 'O')
        {
            words[word_index] = 3;
            string_index += 2;
        }
        else if (word[string_index] == 'N')
        {
            if (word[string_index + 1] == 'O')
            {
                if (word[string_index + 2] == 'T')
                {
                    words[word_index] = 4;
                    string_index += 3;
                }
                else if (word[string_index + 2] == 'R')
                {
                    words[word_index] = 6;
                    string_index += 3;
                }
            }
            else
            {
                words[word_index] = 8;
                string_index += 4;
            }
        }
        else if (word[string_index] == 'X')
        {
            if (word[string_index + 1] == 'O')
            {
                words[word_index] = 5;
                string_index += 3;
            }
            else
            {
                words[word_index] = 7;
                string_index += 4;
            }
        }
        else if (word[string_index] == 'e')
        {
            words[word_index] = 9;
            string_index++;
        }
        else if (word[string_index] == '1' || word[string_index] == '0')
        {
            int result = word[string_index] - 48;
            words[word_index] = result;
            string_index++;
        }
        else
        {
            string_index++;
            word_index--;
        }
        word_index++;

    }


    int size = word_index;
    while (size > 1)
    {
        for (int i = 3; i < size; i++)
        {
            if (words[i] != 9)
                continue;
            else
            {
                bool first_value = words[i - 2], second_value = words[i - 1];
                int x = Operation(first_value, second_value, words[i - 3]);
                for (int j = 0; j < i - 3; j++)
                {
                    temp[j] = words[j];
                }
                temp[i - 3] = x;
                size = size - 3;
                for (int j = i - 2; j < size; j++)
                {
                    temp[j] = words[j + 3];
                }
                for (int j = 0; j < size; j++)
                {
                    words[j] = temp[j];
                }

                break;

            }
        }
    }

    cout << "AND gates : " << andd << "\n";
    cout << "OR gates : " << orr << "\n";
    cout << "NOT gates : " << nott << "\n";
    cout << "XOR gates : " << xorr << "\n";
    cout << "NAND gates : " << nandd << "\n";
    cout << "NOR gates : " << norr << "\n";
    cout << "result : " << words[0];

}

int main()
{
    string str;
    getline(cin, str);
    tokenization(str);
    return 0;
}

// Mariam Hazem Gamgoum 22P0172 and Mariam Ramy 22P0219
