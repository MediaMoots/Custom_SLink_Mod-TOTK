#include "lib.hpp"
#include "nn.hpp"
#include "nn/util/util_snprintf.hpp"
#include "simpleio.hpp"

void OutputDebug(const char *path, const char *output, bool new_line) {

    const size_t output_len = ::strlen(output);
    const size_t file_len   = (new_line == true) ? output_len + 1 : output_len;
    long int last_size = 0; 

    nn::fs::FileHandle output_handle = {};
    u32 result = nn::fs::OpenFile(std::addressof(output_handle), path, nn::fs::OpenMode_Write);
    if (result != 0) {
        nn::fs::CreateFile(path, file_len);
        result = nn::fs::OpenFile(std::addressof(output_handle), path, nn::fs::OpenMode_Write);
    } else {
        nn::fs::GetFileSize(std::addressof(last_size), output_handle);

        nn::fs::SetFileSize(output_handle, file_len + last_size);
    }

    if (result == 0) {
        nn::fs::WriteOption option0(0);
        nn::fs::WriteFile(output_handle, last_size, output, output_len, option0);
        if (new_line == true) {  nn::fs::WriteFile(output_handle, output_len + last_size, "\n", 1, option0); }
        nn::fs::FlushFile(output_handle);

        nn::fs::CloseFile(output_handle);
    }
}

void ReadFileFixed(const char *path, void *in_out_file, u32 size) {

    long int file_size = 0; 

    nn::fs::FileHandle input_handle = {};
    RESULT_ASSERT_PRINT(nn::fs::OpenFile(std::addressof(input_handle), path, nn::fs::OpenMode_Read), "failed to open file");

    nn::fs::GetFileSize(std::addressof(file_size), input_handle);
    ASSERT_PRINT(file_size < size, "ReadFileFixed; file buffer is too small");

    nn::fs::ReadFile(input_handle, 0, in_out_file, file_size);
    nn::fs::CloseFile(input_handle);
}

void OutputFile(const char *path, void *output, size_t output_len) {

    nn::fs::FileHandle output_handle = {};
    u32 create_result = 0xffff'ffff;
    u32 result = nn::fs::OpenFile(std::addressof(output_handle), path, nn::fs::OpenMode_Write);
    if (result != 0) {
        create_result = nn::fs::CreateFile(path, 0);
        result = nn::fs::OpenFile(std::addressof(output_handle), path, nn::fs::OpenMode_Write);
    }

    if (result == 0) {

        long int size = 0;
        nn::fs::GetFileSize(std::addressof(size), output_handle);

        if (static_cast<size_t>(size) != output_len) {
            nn::fs::SetFileSize(output_handle, output_len);
            nn::fs::WriteOption option0(0);
            nn::fs::WriteFile(output_handle, 0, output, output_len, option0);
            nn::fs::FlushFile(output_handle);
        }

        nn::fs::CloseFile(output_handle);
    } else {
        char fail_path[nn::fs::MaxDirectoryEntryNameSize + 1] = {};
        nn::util::SNPrintf(fail_path, sizeof(fail_path), "failed to output decomped file: %s, create_result 0x%x, open_result 0x%x", path, create_result, result);
        ::OutputDebug("sd:/output_failure.txt", fail_path);
    }
}