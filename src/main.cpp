#include <iostream>
#include <fstream>
#include "spirv_cross.hpp"
#include "spirv_msl.hpp"

using namespace spirv_cross;

#define ROOT_DIR "C:/Users/Liam Tyler/Documents/spirvTesting/"

int main(int argc, char** argv) {
    const std::string inputFilename = "resource/shader2.spv";
    std::ifstream in(ROOT_DIR + inputFilename, std::ios::binary);
    if (in.fail()) {
        std::cout << "Failed to open spirv file" << std::endl;
        return 1;
    }
    in.seekg(0, std::ios::end);
    size_t fileSizeInBytes = in.tellg();
    in.seekg(0, std::ios::beg);
    char* spirvData = new char[fileSizeInBytes];
    in.read(spirvData, fileSizeInBytes);
    in.close();
    CompilerMSL compiler((uint32_t*) spirvData, fileSizeInBytes / 4);

    std::string mslText = compiler.compile();
    std::ofstream outputMslFile(ROOT_DIR + inputFilename + ".msl");
    outputMslFile << mslText;
    outputMslFile.close();

    return 0;
}
