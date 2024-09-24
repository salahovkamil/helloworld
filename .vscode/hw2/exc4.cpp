#include <string>
#include <iostream>
int main()
{
   int occurrences = 0;
   std::string::size_type pos = 0;
   std::string s = "тра-та-та";
   std::string target = "та";
   while ((pos = s.find(target, pos )) != std::string::npos) {
          ++ occurrences;
          pos += target.length();
   }
   std::cout << occurrences << std::endl;

}