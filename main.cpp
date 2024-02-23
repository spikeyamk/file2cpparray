#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdint>
#include <filesystem>

void print_usage(const char* argv_0) {
    std::cerr << "Usage: " << argv_0 << " [FILE]\n";
}

void send_bin_name_and_args_to_cout(const int argc, char** argv) {
	std::cerr << argv[0] << ':';
	for(size_t i = 1; i < static_cast<size_t>(argc); i++) {
		std::cerr << " '" << argv[i] << '\'';
		if(i == static_cast<size_t>(argc - 1)) {
			std::cerr << ':';
		}
	}
	std::cerr << ' ';
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        send_bin_name_and_args_to_cout(argc, argv);
        std::cerr << "Invalid input: Needs exactly one argument: number of arguments: " << argc - 1 << std::endl;
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::filesystem::path path { argv[1] };
    std::ifstream file(path, std::ios::binary | std::ios::in);
    
    if(file.is_open() == false) {
        send_bin_name_and_args_to_cout(argc, argv);
        std::cerr << "Error opening file: '" << path.string() << "'\n";
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    std::vector<uint8_t> bytes(std::istreambuf_iterator<char>(file), {});

    std::cout <<
        "----------------------------------//---------------------------------\n"
        "data.hpp\n"
        "#include <array>\n"
        "#include <cstdint>\n"
        "\n"
        "extern const std::array<uint8_t, " << bytes.size() << "> data;\n"
        "----------------------------------//---------------------------------\n"
        "data.cpp\n"
        "\n"
        "const std::array<uint8_t, " << bytes.size() << "> data {";

    for(size_t i = 0; i < bytes.size(); i++) {
        if(i != 0) {
            std::printf(", ");
        }
        if(i % 8 == 0) {
            std::printf("\n    ");
        }
        std::printf("0x%02X", bytes[i]);
    }

    std::printf(
        "\n"
        "};\n"
    );

    return EXIT_SUCCESS;
}
