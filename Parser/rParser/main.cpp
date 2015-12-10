#include "Parser.h"
#include <boost/program_options.hpp>

int main(int argc, char** argv) {
	try {
		namespace po = boost::program_options;
		po::options_description opt;
		std::string config;
		opt.add_options()
			("help,h", "Produce help information..")
			("configuration,c", po::value<std::string>(&config)->required(), "Set path to the configuration file")
		;
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, opt), vm);
		po::notify(vm);
		if(vm.count("help")){
			std::cout << opt << std::endl;
			return EXIT_SUCCESS;
		}
		Parser parser(config);
		parser.Parse();
		return 0;
	} catch (const std::exception& e) {
		Logger::Write(e.what());
	}
}

