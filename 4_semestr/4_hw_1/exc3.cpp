#include <iostream>
#include <sstream>
#include <string>
#include <map>
int main()
{
    std::string str {"я пишу стихи . стихи - это творчество"};
    std::istringstream scin(str);
    std::map<std::string, int> words;
    std::string word, answer;
    int max = 0;
    while(scin >> word)
    {
        words[word]++;
        if(words[word] > max)
        {
            answer = word;
            max = words[word];
        }
    }
    std::cout << answer;
    return 0;
}