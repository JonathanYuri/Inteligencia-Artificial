#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> readFile(string filename)
{
    string line;
    vector<string> lines;
    ifstream fileToRead(filename);
    if (fileToRead.is_open())
    {
        while (getline(fileToRead, line, '\n'))
        {
            string newline = "";
            for (char character: line)
            {
                if (!isspace(character))
                {
                    newline.push_back(character);
                }
            }
            lines.push_back(newline);
        }
        fileToRead.close();
        return lines;
    }
    throw runtime_error("Could not read file");
}

string substring(string line, int inicio, int final)
{
    string subs = "";
    for (int i = inicio; i < final; i++)
    {
        subs.push_back(line[i]);
    }
    return subs;
}

void s2(string line, int *characterStopped)
{
    for (int i = *characterStopped; i < line.length(); i++)
    {
        if (isalpha(line[i]) && isupper(line[i]))
        {
            string subs = substring(line, *characterStopped, i);
            if (subs.compare("true") == 0 || subs.compare("false") == 0)
            {
                cout << subs << " is a keyword" << endl;
                *characterStopped = i;
            }
            else
            {
                // erro
                *characterStopped = -1;
            }
            return;
        }
        if (!isalnum(line[i]))
        {
            string subs = substring(line, *characterStopped, i);
            if (subs.compare("true") == 0 || subs.compare("false") == 0)
            {
                cout << subs << " is a keyword" << endl;
            }
            else
            {
                cout << subs << " is a identifier" << endl;
            }
            
            *characterStopped = i;
            return;
        }
    }

    string subs = substring(line, *characterStopped, line.length());
    if (subs.compare("true") == 0 || subs.compare("false") == 0)
    {
        cout << subs << " is a keyword" << endl;
    }
    else
    {
        cout << subs << " is a identifier" << endl;
    }
    *characterStopped = -1;
    return;
}

void s3(string line, int *characterStopped)
{
    for (int i = *characterStopped; i < line.length(); i++)
    {
        if (isalpha(line[i]))
        {
            if (islower(line[i]))
            {
                // print
                string subs = substring(line, *characterStopped, i);
                cout << subs << " is a keyword" << endl;
                *characterStopped = i;
                return;
            }
        }
        else
        {
            // print
            string subs = substring(line, *characterStopped, i);
            cout << subs << " is a keyword" << endl;
            *characterStopped = i;
            return;
        }
    }

    // print
    string subs = substring(line, *characterStopped, line.length());
    cout << subs << " is a keyword" << endl;
    *characterStopped = -1;
    return;
}

void s1(string line, int *characterStopped)
{
    if (islower(line[*characterStopped]))
    {
        s2(line, characterStopped);
    }
    else
    {
        s3(line, characterStopped);
    }
}

void s4(string line, int *characterStopped)
{
    char op = line[*characterStopped];

    *characterStopped += 1;
    cout << op << " is a operator" << endl;;

    if (*characterStopped >= line.length())
    {
        *characterStopped = -1;
        return;
    }

    if (isalpha(line[*characterStopped]))
    {
        if (islower(line[*characterStopped]))
        {
            // print
            return;
        }
    }
    throw runtime_error("error de sintaxe, esperando letra minuscula depois de operador\nlinha: " + line + "caractere" + line[*characterStopped]);
}

void s0(string line, int *characterStopped)
{
    if (isalpha(line[*characterStopped]))
    {
        s1(line, characterStopped);
    }
    else
    {
        s4(line, characterStopped);
    }
}

vector<string> analyzer(vector<string> lines)
{
    for (string line : lines)
    {
        int character_stopped = 0;
        while (character_stopped != -1)
        {
            s0(line, &character_stopped);
        }
    }
}

int main()
{
    vector<string> lines = readFile("rules.txt");
    for (string line : lines)
    {
        cout << line << endl;
    }
    
    cout << endl;
    vector<string> tokens = analyzer(lines);

    return 0;
}