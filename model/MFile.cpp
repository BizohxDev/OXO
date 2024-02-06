#include "MFile.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <codecvt>
#include "MLogs.hpp"

/** * * * * * * **
 *  CONSTRUCTOR  *
 ** * * * * * * **/
MFile::MFile() {}

/** * * * * * * **
 *    SETTER     *
 ** * * * * * * **/
void MFile::setText(const std::wstring &text) {
    m_text = text;
}

/** * * * * * * **
 *    GETTER     *
 ** * * * * * * **/
std::wstring MFile::getText() const {
    return m_text;
}

/** * * * * * * **
 *   FUNCTIONS   *
 ** * * * * * * **/
bool MFile::readFile(const std::string &filePath) {
    // Opening the file in binary mode
    std::wifstream file(filePath, std::ios::binary);

    // Check opening
    if (!file.is_open()) {
        // Error occurred
        createLog("An error occurred while reading file : " + filePath);
        return false;
    }

    // Define locale for UTF-8 to wchar_t conversion
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);

    // Use the new locale in the feed
    file.imbue(utf8_locale);

    // Read the contents of the file using wistream
    std::wstringstream wss;
    wss << file.rdbuf();

    // Close the file
    file.close();

    // Save the content
    m_text = wss.str();
    return true;
}

bool MFile::writeFile(const std::string &filePath, const std::string &fileName) {
    // To do
    return false;
}
