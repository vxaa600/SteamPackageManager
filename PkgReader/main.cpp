#include <iostream>
#include <filesystem>
#include <string>
#include <print>
#include <getopt.h>
#include <steam.h>
namespace fs = std::filesystem;

int wmain(int argc, wchar_t* argv[])
{
	std::println("steam package extractor v1");
	fs::path inputfile;
	fs::path outputfile;
	int c;
    while((c=getopt(argc,argv,L":i:o:h")) != -1)
	{
		switch (c)
		{
		case 'i':
			inputfile = optarg;
			break;

		case 'o':
			outputfile = optarg;
			break;

		case 'h':
			std::println("usage: PkgReader.exe -i file.pkg -o outputdir");
			return 0;
		}
	}
	if (inputfile.empty() || outputfile.empty())
	{
		std::println("usage: PkgReader.exe -i file.pkg -o outputdir");
		return 1;
	}
	package_unpack(inputfile.string(), outputfile.string());
	std::println("Extracted {} to {}", inputfile.string(), outputfile.string());
}