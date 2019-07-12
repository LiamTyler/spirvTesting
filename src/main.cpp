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

    auto executionModel = compiler.get_execution_model();
    spirv_cross::MSLResourceBinding newBinding;
    newBinding.stage = executionModel;
    auto resources = compiler.get_shader_resources();
    printf("Shader Resources: Uniform buffers\n");
    for (const auto& resource : resources.uniform_buffers) {
        unsigned set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
        unsigned binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
        printf("Uniform Buffer %s at set = %u, binding = %u\n", resource.name.c_str(), set, binding);
        newBinding.desc_set = set;
        newBinding.binding = binding;
        newBinding.msl_buffer = binding;
        //newBinding.msl_sampler = binding;
        //newBinding.msl_texture = binding;
        compiler.add_msl_resource_binding(newBinding);
    }
    printf("Shader Resources: storage_buffers\n");
    for (const auto& resource : resources.storage_buffers) {
        unsigned set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
        unsigned binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
        printf("storage_buffer Buffer %s at set = %u, binding = %u\n", resource.name.c_str(), set, binding);
        newBinding.desc_set = set;
        newBinding.binding = binding;
        newBinding.msl_buffer = binding;
        //newBinding.msl_sampler = binding;
        //newBinding.msl_texture = binding;
        compiler.add_msl_resource_binding(newBinding);
    }

    std::string mslText = compiler.compile();
    std::ofstream outputMslFile(ROOT_DIR + inputFilename + ".msl");
    outputMslFile << mslText;
    outputMslFile.close();

    return 0;
}
