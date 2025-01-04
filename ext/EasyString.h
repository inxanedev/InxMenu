#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#define ES_WHITESPACE " \n\r\t\f\v"
#define ES_ALPHABET_LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define ES_ALPHABET_UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ES_ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ES_NUMERIC "0123456789"
#define ES_ALPHANUMERIC "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define ES_SPECIAL "!@#$%^&*()_+-=[]{}\\|;'./:\">?`~"
#define ES_ALPHANUMERICSPECIAL "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}\\|;'./:\">?`~"

/// Namespace containing the functionality of the EasyString library.
namespace easystring {
    /// Makes the string uppercase.
    inline std::string uppercase(const std::string& text) {
        std::ostringstream result;
        for (int i = 0; i < text.length(); i++) {
            result << static_cast<char>(toupper(text[i]));
        }
        return result.str();
    }

    /// Makes the string lowercase.
    inline std::string lowercase(const std::string& text) {
        std::ostringstream result;
        for (int i = 0; i < text.length(); i++) {
            result << static_cast<char>(tolower(text[i]));
        }
        return result.str();
    }

    /// Puts `amount` of `c` to the left of `text`.
    inline std::string pad_left(const std::string& text, size_t amount, char c = ' ') {
        std::ostringstream result;
        for (int i = 0; i < amount; i++) {
            result << c;
        }
        result << text;
        return result.str();
    }

    /// Puts `amount` of `c` to the right of `text`.
    inline std::string pad_right(const std::string& text, size_t amount, char c = ' ') {
        std::ostringstream result;
        result << text;
        for (int i = 0; i < amount; i++) {
            result << c;
        }
        return result.str();
    }

    /// Transforms a string into the title case.
    inline std::string title_case(const std::string& text) {
        std::ostringstream result;

        std::istringstream iss(text);
        do {
            std::string word;
            std::ostringstream transformed_word;
            iss >> word;
            for (int i = 0; i < word.length(); i++) {
                if (i == 0) transformed_word << static_cast<char>(toupper(word[0]));
                else transformed_word << static_cast<char>(tolower(word[i]));
            }
            result << transformed_word.str() << ' ';
        } while (iss);

        std::string to_trim = result.str();
        return to_trim.substr(0, to_trim.length() - 1);
    }

    /// Split a string into a list of strings, using a string delimiter.
    inline std::vector<std::string> split(std::string text, const std::string& delim) {
        std::vector<std::string> result;
        size_t pos = 0;
        std::string token;
        while ((pos = text.find(delim)) != std::string::npos) {
            token = text.substr(0, pos);
            result.push_back(token);
            text.erase(0, pos + delim.length());
        }
        result.push_back(text);
        return result;
    }

    /// Justify the string from the left with `c`, until the whole string reaches length `length`.
    inline std::string left_justify(const std::string& text, char c, size_t length) {
        int amount = length - text.length();
        if (amount < 1) return text;

        std::ostringstream result;
        for (int i = 0; i < amount; i++) {
            result << c;
        }
        result << text;
        return result.str();
    }

    /// Justify the string from the right with `c`, until the whole string reaches length `length`.
    inline std::string right_justify(const std::string& text, char c, size_t length) {
        int amount = length - text.length();
        if (amount < 1) return text;

        std::ostringstream result;
        result << text;
        for (int i = 0; i < amount; i++) {
            result << c;
        }
        return result.str();
    }

    /// Removes all whitespace from the left of the string.
    inline std::string trim_left(const std::string& text) {
        size_t start = text.find_first_not_of(ES_WHITESPACE);
        return (start == std::string::npos) ? "" : text.substr(start);
    }

    /// Removes all whitespace from the right of the string.
    inline std::string trim_right(const std::string& text) {
        size_t end = text.find_last_not_of(ES_WHITESPACE);
        return (end == std::string::npos) ? "" : text.substr(0, end + 1);
    }

    /// Removes all leading and trailing whitespace from the string.
    inline std::string trim(const std::string& text) {
        return trim_left(trim_right(text));
    }

    /// Reverses a string.
    inline std::string reverse(const std::string& text) {
        std::ostringstream result;
        for (int i = text.length() - 1; i >= 0; i--) {
            result << text[i];
        }
        return result.str();
    }

    /// Returns true if `text` starts with `prefix`.
    inline bool starts_with(const std::string& text, const std::string& prefix) {
        return text.find(prefix) == 0;
    }

    /// Returns true if `text` ends with `prefix`
    inline bool ends_with(const std::string& text, const std::string& suffix) {
        if (suffix.length() > text.length()) return false;
        return text.compare(text.length() - suffix.length(), suffix.length(), suffix) == 0;
    }

    /// Returns true if `text` contains `other`.
    inline bool contains(const std::string& text, const std::string& other) {
        return text.find(other) != std::string::npos;
    }

    /// Returns true if all characters in `text` are uppercase.
    inline bool is_upper(const std::string& text) {
        for (int i = 0; i < text.length(); i++) {
            if (!isupper(text[i])) return false;
        }
        return true;
    }

    /// Returns true if all characters in `text` are lowercase.
    inline bool is_lower(const std::string& text) {
        for (int i = 0; i < text.length(); i++) {
            if (!islower(text[i])) return false;
        }
        return true;
    }

    /// Replace all occurences of `from` with `to` in `text`.
    inline std::string replace(std::string text, const std::string& from, const std::string& to) {
        size_t pos = 0;
        while ((pos = text.find(from, pos)) != std::string::npos) {
            text.replace(pos, from.length(), to);
            pos += to.length();
        }
        return text;
    }

    /// Replace everything in `text` using the from -> to map in `map`.
    inline std::string replace(std::string text, const std::unordered_map<std::string, std::string> map) {
        for (const std::pair<std::string, std::string> transform : map) {
            text = replace(text, transform.first, transform.second);
        }
        return text;
    }

    /// Joins all the strings in `strings`, optionally provide a separator
    inline std::string join(const std::vector<std::string>& strings, const std::string& separator = "") {
        std::ostringstream result;
        for (int i = 0; i < strings.size(); i++) {
            result << strings[i];
            if (i != strings.size() - 1) result << separator;
        }
        return result.str();
    }

    /// Capitalizes the first letter of the string.
    inline std::string capitalize(const std::string& text) {
        std::string result = text;
        result[0] = toupper(result[0]);

        return result;
    }

    /// Splits the string into two at the specified index, and returns an std::pair containing both of them.
    inline std::pair<std::string, std::string> partition(const std::string& text, size_t index) {
        return std::make_pair(text.substr(0, index), text.substr(index));
    }

    /// Converts a string into a vector of `char`s.
    inline std::vector<char> to_char_vector(const std::string& text) {
        return std::vector<char>(text.begin(), text.end());
    }

    /// Repeats a string `amount` of times.
    inline std::string repeat(const std::string& text, unsigned int amount) {
        std::ostringstream result;
        for (int i = 0; i < amount; i++) {
            result << text;
        }
        return result.str();
    }
}