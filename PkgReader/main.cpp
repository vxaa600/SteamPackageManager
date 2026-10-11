#include <iostream>
#include <filesystem>
#include <string>
#include <print>
#include <getopt.h>
#include <steam.h>
namespace fs = std::filesystem;

int wmain(int argc, wchar_t* argv[])
{
	std::println("steam package manager v2");
	fs::path inputfile;
	fs::path outputfile;

	bool extract{ false };
	bool write{ false };
	int c;
    while((c=getopt(argc,argv,L"ew:i:o:h")) != -1)
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
			std::println("usage: spmpp.exe -e|-w -i file.pkg -o outputdir");
			return 0;
		}
	}
	if (extract == write || inputfile.empty() || outputfile.empty())
	{
		std::println("usage: spmpp.exe -e|-w -i file.pkg -o outputdir");
		return 1;
	}
	if (extract)
	{
		package_unpack(inputfile.string(), outputfile.string());
		std::println("Extracted {} to {}", inputfile.string(), outputfile.string());
	}
	else if (write)
	{
		package_unpack(inputfile.string(), outputfile.string());
		std::println("Written to {}",outputfile.string());
	}
	

}