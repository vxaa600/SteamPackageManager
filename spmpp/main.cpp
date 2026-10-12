#include <iostream>
#include <filesystem>
#include <string>
#include <print>
#include <steam.h>
namespace fs = std::filesystem;

int wmain(int argc, wchar_t* argv[])
{
	std::cout << "steam package manager\n";
	std::cout << "made by vxaa\n";
	fs::path inputfile;
	fs::path outputfile;

	bool extract{ false };
	bool pack{ false };
    for (int i = 1; i < argc; i++)
    {
        std::wstring arg{ argv[i] };

        if (arg.size() != 2 || arg[0] != L'-')
        {
            std::println("invalid argument");
            return 1;
        }

        switch (arg[1])
        {
        case L'e':
            extract = true;
            break;

        case L'p':
            pack = true;
            break;

        case L'i':
            if (i + 1 >= argc)
            {
                std::println("missing input");
                return 1;
            }
            inputfile = argv[++i];
            break;

        case L'o':
            if (i + 1 >= argc)
            {
                std::println("missing output");
                return 1;
            }
            outputfile = argv[++i];
            break;

        case L'h':
            std::println("usage: spmpp.exe -e | -p -i input -o output");
            return 0;

        default:
            std::println("invalid argument");
            return 1;
        }
    }
	if (extract == pack || inputfile.empty() || outputfile.empty())
	{
		std::cout << "usage: spmpp.exe -e | -p -i input -o output\n";
		return 1;
	}
	if (pack && outputfile.extension() != ".pkg")
	{
		std::cout << "incorrect file type!\n";
		return 1;
	}
	else if (extract && inputfile.extension() != ".pkg")
	{
		std::cout << "incorrect file type!";
		return 1;
	}
	if (extract)
	{
		package_unpack(inputfile.string(), outputfile.string());
		std::println("extracted {} to {}", inputfile.string(), outputfile.string());
	}
	else if (pack)
	{
		package_pack(inputfile.string(), outputfile.string());
		std::println("written to {}",outputfile.string());
	}
	

}