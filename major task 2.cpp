#include <cstring>
#include <cctype>
#include <string>
#include<iostream>
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

string varcheck(string word)
{
    //a b c a b c 
    int wordsize = word.size();
    int varcheck = 2;
    int vars[100] = { 0 };
    int num_of_vars = 0;
    bool flag = false;
    while (varcheck < wordsize - 1) {
        if (word[varcheck] != 'E' && word[varcheck - 1] == ' ' && word[varcheck + 1] == ' ' && word[varcheck] > 64 && word[varcheck] < 91)
        {
            if (word[varcheck] == 'E')
                continue;
            flag = false;
            if (num_of_vars == 0)
            {
                vars[0] = word[varcheck];
                num_of_vars++;
                varcheck++;
                continue;
            }
            for (int j = 0; j < num_of_vars; j++)
            {
                if (word[varcheck] == vars[j])
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                num_of_vars++;
                vars[num_of_vars] = word[varcheck];
                varcheck++;
            }

        }

        varcheck++;
    }
    string newvar = "";
    string uppercaseString = "";
    if (num_of_vars) {
        cout << num_of_vars << " varaibles are missing please enter them in separate lines" << endl;
        int counter = 0;
        while (counter < num_of_vars)
        {
            getline(cin, newvar);
            for (char character : newvar) {
                uppercaseString += toupper(character);
            }
            for (int i = 1; i < wordsize - 1; i++) {
                if (word[i] == uppercaseString[0] && word[i - 1] == ' ' && word[i + 1] == ' ') {
                    word[i] = uppercaseString[2];
                }
                continue;
            }
            counter++;
            newvar = "";
            uppercaseString = "";
        }
    }
    return word;
}

// function to convert into numbers and inserts it into an array and modifies it accordingly
void tokenization(string word)
{
    bool first_value, second_value = false;
    int words[100] = { 0 };
    int temp[100] = { 0 };
    int string_index = 0;
    int word_index = 0;
    bool flag = false;

    int wordsize = word.size();
    while (string_index < wordsize)
    {
        if (word[string_index] == 'A' && word[string_index + 1] == 'N' && word[string_index + 2] == 'D' && word[string_index + 3] == ' ')
        {
            words[word_index] = 2;
            string_index += 3;
            word_index++;
            continue;
        }
        else if (word[string_index] == 'O' && word[string_index + 1] == 'R' && word[string_index + 2] == ' ')
        {
            words[word_index] = 3;
            word_index++;
            string_index += 2;
            continue;
        }
        else if (word[string_index] == 'N' && word[string_index + 1] == 'O' && word[string_index + 2] == 'T' && word[string_index + 3] == ' ')
        {
            words[word_index] = 4;
            string_index += 3;
            word_index++;
            continue;
        }
        else if (word[string_index] == 'N' && word[string_index + 1] == 'O' && word[string_index + 2] == 'R' && word[string_index + 3] == ' ')
        {
            words[word_index] = 6;
            string_index += 3;
            word_index++;
            continue;
        }
        else if (word[string_index] == 'N' && word[string_index + 1] == 'A' && word[string_index + 2] == 'N' && word[string_index + 3] == 'D' && word[string_index + 4] == ' ')
        {
            words[word_index] = 8;
            string_index += 4;
            word_index++;
            continue;
        }
        else if (word[string_index] == 'X' && word[string_index + 1] == 'O' && word[string_index + 2] == 'R' && word[string_index + 3] == ' ')
        {
            words[word_index] = 5;
            string_index += 3;
            word_index++;
            continue;
        }
        else if (word[string_index] == 'X' && word[string_index + 1] == 'N' && word[string_index + 2] == 'O' && word[string_index + 3] == 'R' && word[string_index + 4] == ' ')
        {
            words[word_index] = 7;
            string_index += 4;
            word_index++;
            continue;
        }
        else if (word[string_index] == 'E')
        {
            words[word_index] = 9;
            string_index++;
            word_index++;
            continue;
        }
        else if (word[string_index] == '1' || word[string_index] == '0')
        {
            words[word_index] = word[string_index] - 48;
            string_index += 1;
            word_index++;
            continue;
        }
        else if (word[string_index] == ' ')
        {
            string_index++;
            continue;
        }
        else
        {
            cout << "Wrong Logic Circuit Description \n";
            flag = true;
            string_index++;
            break;
        }
    }

    int size = word_index;
    for (int i = 3; i < size; i++) {
        if (words[i] == 9) {
            if (words[i - 3] == 4)
            {
                flag = true;
                cout << "result : BAD input : missing input number\n";
                break;
            }
            if ((words[i - 1] == 1 || words[i - 1] == 0) && (words[i - 2] != 1 && words[i - 2] != 0)) {
                if (words[i - 2] == 4)
                    continue;
                else
                {
                    flag = true;
                    cout << "result : BAD input : missing input number\n";
                    break;
                }
            }
        }
    }


    while (size > 1)
    {
        if (size == 3 && words[0] == 4)
        {
            words[0] = Operation(words[1], 0, 4);
            break;
        }
        else {
            for (int i = 3; i < size; i++)
            {
                if (words[i] != 9)
                    continue;
                else
                {
                    int x;
                    if (words[i - 2] == 4)
                    {
                        x = Operation(words[i - 1], 0, 4);
                        for (int j = 0; j < i - 2; j++)
                        {
                            temp[j] = words[j];
                        }
                        temp[i - 2] = x;
                        size = size - 2;
                        for (int j = i - 1; j < size; j++)
                        {
                            temp[j] = words[j + 2];
                        }
                        for (int j = 0; j < size; j++)
                        {
                            words[j] = temp[j];
                        }
                        continue;
                    }
                    else
                    {
                        if (words[i - 3] == 4)
                        {

                        }
                        bool first_value = words[i - 2], second_value = words[i - 1];
                        x = Operation(first_value, second_value, words[i - 3]);
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
        }
    }
    if (!flag)
    {
        cout << "AND gates : " << andd << "\n";
        cout << "OR gates : " << orr << "\n";
        cout << "NOT gates : " << nott << "\n";
        cout << "XOR gates : " << xorr << "\n";
        cout << "NAND gates : " << nandd << "\n";
        cout << "NOR gates : " << norr << "\n";
        cout << "result : " << words[0];
    }

}

int main()
{
    string str, uppercaseString;
    getline(cin, str);
    for (char character : str)
    {
        uppercaseString += toupper(character);
    }
    str = varcheck(uppercaseString);
    tokenization(str);
    return 0;
}