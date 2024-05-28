int handleArguments(int argc, char **argv) {
	for(int x = 1; x < argc; x++) {
		if (x < 4) {
			std::cout << "\t x < 4" << '\n';
		} 

		if (x < argc) {
			std::cout << "\t x < argc" << '\n';
		} 

		std::cout << "x: " << x << '\n';
		std::cout << "argc: " << argc << "\n\n";

		if(argv[x][0] != '-') {
			std::cout << argv[x] << "argument must start with '-' and be followed by a single character. Terminating";
			return -1; 
		} 

		if(argv[x][1] == 'd' || argv[x][1] == 'D') {
			debug = true;
			std::cout << "Debug mode is enabled. Registers and Memory after PC will be displayed. " << std::endl;
		} else if(argv[x][1] == 'f' || argv[x][1] == 'F') {
			if(standardInput) {
				std::cout << "You can't read memory from standard input and a binarie. Terminating\n";
				return -1;
			}
			file = true;
			std::cout << "File mode is enabled." << std::endl;
		} else if(argv[x][1] == 'i' || argv[x][1] == 'I') {
			standardInput = true;
			std::cout << "Standard input mode is enabled. System memory will be loaded from stdin" << std::endl;
		} else if(argv[x][1] == 's' || argv[x][1] == 'S') {
			sdl = true;
			std::cout << "Sdl will attempt to start." << std::endl;
		} else {
			std::cout << argv[x] <<" is not a legal argument. Terminating" << std::endl;
			return -1;
		}
		std::cout << '\n';
	}	
}
