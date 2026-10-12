#include <iostream>
#include <filesystem>
#include <string>
#include <print>
#include <getopt.h>
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
	int c;
	while ((c = getopt(argc, argv, L"epi:o:h")) != -1)
	{
		switch (c)
		{
		case 'e':
			extract = true;
			break;

		case 'p':
			pack = true;
			break;
		case 'i':
			inputfile = optarg;
			break;

		case 'o':
			outputfile = optarg;
			break;

		case 'h':
			std::cout << "usage: spmpp.exe -e (extract) | -p (pack) -i file.pkg/inputdir -o outputdir/output.pkg\n";
			return 0;
		}
	}
	if (extract == pack || inputfile.empty() || outputfile.empty())
	{
		std::cout << "usage: spmpp.exe -e (extract) | -p (pack) -i file.pkg/inputdir -o outputdir/output.pkg\n";
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