#include <iostream>
#include <filesystem>
#include <string>
#include <print>
#include <getopt.h>
#include <steam.h>
namespace fs = std::filesystem;

int wmain(int argc, wchar_t* argv[])
{
	std::println("steam package manager");
	std::println("made by vxaa");
	fs::path inputfile;
	fs::path outputfile;

	bool extract{ false };
	bool write{ false };
	int c;
	while ((c = getopt(argc, argv, L"ewi:o:h")) != -1)
	{
		switch (c)
		{
		case 'e':
			extract = true;
			break;

		case 'w':
			write = true;
			break;
		case 'i':
			inputfile = optarg;
			break;

		case 'o':
			outputfile = optarg;
			break;

		case 'h':
			std::cout << "usage: spmpp.exe -e|-w -i file.pkg -o outputdir\n";
			return 0;
		}
	}
	if (extract == write || inputfile.empty() || outputfile.empty())
	{
		std::cout << "usage: spmpp.exe -e|-w -i file.pkg -o outputdir\n";
		return 1;
	}
	if (write && outputfile.extension() != ".pkg")
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
	else if (write)
	{
		package_pack(inputfile.string(), outputfile.string());
		std::println("written to {}",outputfile.string());
	}
	

}