
#include <fstream>
#include <vector>
#include <cassert>
#include <boost/progress.hpp>

static size_t getFileSize(FILE* file) {
    fseek(file, 0, SEEK_END);
    size_t read_len = ftell(file);
    fseek(file, 0, SEEK_SET);
    return read_len;
}

static size_t getFileSize(const char* filePath) {
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        return 0;
    }
    size_t size = getFileSize(file);
    fclose(file);
    return size;
}


std::vector<unsigned char> readFromFile1(const char* filePath) {
    FILE* file = fopen(filePath, "rb");
    if (file == NULL)
        exit(-1);
    std::vector<unsigned char> result;
    if (file == NULL) {
        return result;
    }

    size_t fileSize = getFileSize(file);
    std::cout << fileSize << std::endl;
    if (fileSize != 0) {
        result.resize(fileSize);
        size_t n = fread(&result[0], 1, fileSize, file);
        assert(n <= fileSize);
        if (n != fileSize) {
            result.resize(n);
        }
    }
    
    fclose(file);
    return result;
}


std::vector<unsigned char> readFromFile2(const char* filePath) {
    std::ifstream inputFile(filePath, std::ios::binary);
    std::vector<unsigned char> fileData((std::istreambuf_iterator<char>(inputFile)),
                                        std::istreambuf_iterator<char>());
    return fileData;
}


std::vector<unsigned char> readFromFile3(const char* filePath) {
    std::vector<unsigned char> fileData;
    fileData.reserve(getFileSize(filePath));
    
    std::ifstream inputFile(filePath, std::ios::binary);
    fileData.insert(fileData.end(),
                    std::istreambuf_iterator<char>(inputFile),
                    std::istreambuf_iterator<char>());
    
    return fileData;
}


std::vector<unsigned char> readFromFile4(const char* filePath) {
    std::vector<unsigned char> fileData;
    std::ifstream inputFile(filePath, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "error" << std::endl;
    }
    inputFile.seekg(0, std::ios::end);
    fileData.resize(inputFile.tellg());
    inputFile.seekg(0);
    std::cout << fileData.size() << std::endl;
    
    inputFile.read(reinterpret_cast<char*>(fileData.data()), fileData.size());

    return fileData;
}


int main(int argc, const char* argv[]) {
    const char* filePath = "b.mp4";

    readFromFile1(filePath);


    return 0;
}
