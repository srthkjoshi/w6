#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_TEXTFILE_H_
#define SDDS_TEXTFILE_H_

#include <iostream>
#include <fstream>
#include <string>

namespace sdds {

    class Line {
        char* m_value{ nullptr };
        size_t m_size{ 0u };
    public:
        Line() {}
        Line(const char* lineContent) { *this = lineContent; }
        Line& operator=(const char* lineContent) {
            delete[] m_value;
            m_value = nullptr;
            if (lineContent != nullptr && lineContent[0] != '\0') {
                m_value = new char[strlen(lineContent) + 1];
                strcpy_s(m_value, strlen(lineContent) + 1, lineContent);
                m_size = strlen(lineContent);
            }
            return *this;
        }
        ~Line() { delete[] m_value; }
        operator const char* () const { return m_value; }
        size_t size() const { return m_size; }
    };

    class TextFile {
        Line* m_textLines{ nullptr };
        char* m_filename{ nullptr };
        unsigned m_noOfLines{ 0u };
        unsigned m_pageSize{ 0u };
        void setFilename(const char* fname, bool isCopy = false);
        void setNoOfLines();
        void loadText();
        void saveAs(const char* fileName) const;
        void setEmpty();
    public:
        TextFile(unsigned pageSize = 15);
        TextFile(const char* filename, unsigned pageSize = 15);
        TextFile(const TextFile&);
        TextFile& operator=(const TextFile&);
        ~TextFile();
        std::ostream& view(std::ostream& ostr) const;
        std::istream& getFile(std::istream& istr);
        operator bool() const;
        unsigned lines() const;
        const char* name() const;
        const char* operator[](unsigned index) const;
    };

    std::ostream& operator<<(std::ostream& ostr, const TextFile& text);
    std::istream& operator>>(std::istream& istr, TextFile& text);

}

#endif // SDDS_TEXTFILE_H_
