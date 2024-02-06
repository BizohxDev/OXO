#ifndef OXO_MFILE_HPP
#define OXO_MFILE_HPP

#include <string>

class MFile {
protected:
    std::wstring m_text;

private:

public:
    // Constructor
    MFile();

    // Setter
    void setText(const std::wstring &text);

    // Getter
    std::wstring getText() const;

    // Functions
    bool readFile(const std::string &filePath);
    bool writeFile(const std::string &filePath, const std::string &fileName);
};

#endif //OXO_MFILE_HPP
