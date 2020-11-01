#ifndef KEYWORDS_IN_FILE
#define KEYWORDS_IN_FILE

#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>

class KeywordsInFile
{
    public:
        KeywordsInFile() = delete; //disable default constructor

        KeywordsInFile ( const std::string& filename_with_keywords, const std::string& filename_with_text )
        {
            std::ifstream keywords_file;
            keywords_file.open(filename_with_keywords);

            if (keywords_file.is_open())
            {
                std::string line;
                std::string modified_line;
                while (getline(keywords_file, line))
                {
                    modified_line = "";
                    //replace all non-letters with spaces
                    for (char& c: line)
                        if (std::isalpha(c))
                            modified_line += c;
                        else
                            modified_line += ' ';

                    std::stringstream ss(modified_line);
                    std::string word;
                    while (ss >> word)
                        keywords.insert(word); total_occurrences.insert({word, 0});
                }
                keywords_file.close();
            }


            std::ifstream text_file;
            text_file.open(filename_with_text);

            if (text_file.is_open())
            {
                std::string line;
                std::string modified_line;
                while (getline(text_file, line))
                {
                    modified_line = "";
                    for (char& c: line)
                        if (std::isalpha(c))
                            modified_line += c;
                        else
                            modified_line += ' ';

                    std::map<std::string, int> new_map;
                    occurrences_per_line.push_back(new_map);

                    std::stringstream ss(modified_line);
                    std::string word;
                    while (ss >> word){
                        if (KeywordFound(word)){
                            total_occurrences.at(word)++;
                            if (occurrences_per_line.back().count(word) > 0)
                                occurrences_per_line.back().at(word)++;
                            else
                                occurrences_per_line.back().insert({word, 1});
                        }
                    }
                }
                text_file.close();
            }
        }

        bool KeywordFound( const std::string& keyword )
        {
            if (keywords.count(keyword) > 0)
                return true;
            else
                return false;
        }

        //@PRE: line_number starts from 1
        int KeywordInLine( const std::string& keyword, const int& line_number )
        {
            if (occurrences_per_line[line_number-1].count(keyword) > 0)
                return occurrences_per_line[line_number-1].at(keyword);
            else
                return 0;
        }

        int TotalOccurrences( const std::string& keyword )
        {
            if (total_occurrences.count(keyword) > 0)
                return total_occurrences.at(keyword);
            else
                return 0;
        }

        friend std::ostream& operator<<(std::ostream& out, const KeywordsInFile& kif);

    private:
        std::unordered_set<std::string> keywords;
        std::unordered_map<std::string, int> total_occurrences;
        std::vector<std::map<std::string, int>> occurrences_per_line; //occurrences_per_line[N].at(word) gives # of times word appears at line N
};

std::ostream& operator<<(std::ostream& out, const KeywordsInFile& kif)
{
    for (const auto& word: kif.keywords)
        out << word << '\n';
    return out;
}

#endif