#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include "TextFile.h"

namespace sdds {

    TextFile::TextFile(unsigned pageSize) {
        m_textLines = nullptr;
        m_filename = nullptr;
        m_noOfLines = 0;
        m_pageSize = pageSize;
    }

    TextFile::TextFile(const char* filename, unsigned pageSize) {
        m_textLines = nullptr;
        m_filename = nullptr;
        m_noOfLines = 0;
        m_pageSize = pageSize;
        setFilename(filename);
        setNoOfLines();
        loadText();
    }

    TextFile::TextFile(const TextFile& other) {
        m_textLines = nullptr;
        m_filename = nullptr;
        m_noOfLines = 0;
        m_pageSize = 0;
        *this = other;
    }

    TextFile& TextFile::operator=(const TextFile& other) {
        if (this != &other) {
            delete[] m_textLines;
            delete[] m_filename;
            m_textLines = new Line[other.m_noOfLines];
            for (size_t i = 0; i < other.m_noOfLines; i++) {
                m_textLines[i] = other.m_textLines[i];
            }
            m_filename = new char[strlen(other.m_filename) + 1];
            strcpy_s(m_filename, strlen(other.m_filename) + 1, other.m_filename);
            m_noOfLines = other.m_noOfLines;
            m_pageSize = other.m_pageSize;
        }
        return *this;
    }

    TextFile::~TextFile() {
        delete[] m_textLines;
        delete[] m_filename;
    }

    void TextFile::setFilename(const char* fname, bool isCopy) {
        delete[] m_filename;
        if (isCopy) {
            m_filename = new char[strlen(fname) + 3];
            strcpy_s(m_filename, strlen(fname) + 3, "C_");
        }
        else {
            m_filename = new char[strlen(fname) + 1];
            *m_filename = '\0';
        }
        strcat(m_filename, fname);
    }

    void TextFile::setNoOfLines() {
        std::ifstream file(m_filename);
        char ch;
        while (file.get(ch)) {
            if (ch == '\n') {
                m_noOfLines++;
            }
        }
        file.clear();
        file.seekg(0, std::ios::beg);
    }

    void TextFile::loadText() {
        std::ifstream file(m_filename);
        if (file.is_open()) {
            m_textLines = new Line[m_noOfLines];
            for (size_t i = 0; i < m_noOfLines; i++) {
                std::string line;
                std::getline(file, line);
                m_textLines[i] = line.c_str();
            }
            file.close();
        }
    }

    void TextFile::saveAs(const char* fileName) const {
        std::ofstream file(fileName);
        if (file.is_open()) {
            for (size_t i = 0; i < m_noOfLines; i++) {
                file << m_textLines[i] << std::endl;
            }
            file.close();
        }
    }

    void TextFile::setEmpty() {
        delete[] m_textLines;
        delete[] m_filename;
        m_textLines = nullptr;
        m_filename = nullptr;
        m_noOfLines = 0;
        m_pageSize = 0;
    }

    std::ostream& TextFile::view(std::ostream& ostr) const {
        if (m_filename != nullptr) {
            ostr << m_filename << std::endl;
            ostr << "==========" << std::endl;
            for (size_t i = 0; i < m_noOfLines; i++) {
                ostr << m_textLines[i] << std::endl;
                if ((i + 1) % m_pageSize == 0) {
                    ostr << "Hit ENTER to continue...";
                    std::cin.get();
                    std::cin.ignore();
                }
            }
        }
        return ostr;
    }

    std::istream& TextFile::getFile(std::istream& istr) {
        std::string filename;
        istr >> filename;
        setFilename(filename.c_str());
        setNoOfLines();
        loadText();
        return istr;
    }

    TextFile::operator bool() const {
        return m_filename != nullptr;
    }

    unsigned TextFile::lines() const {
        return m_noOfLines;
    }

    const char* TextFile::name() const {
        return m_filename;
    }

    const char* TextFile::operator[](unsigned index) const {
        if (index >= m_noOfLines) {
            return nullptr;
        }
        return m_textLines[index];
    }

    std::ostream& operator<<(std::ostream& ostr, const TextFile& text) {
        return text.view(ostr);
    }

    std::istream& operator>>(std::istream& istr, TextFile& text) {
        return text.getFile(istr);
    }

}