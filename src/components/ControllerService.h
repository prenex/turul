#ifndef CONTROLLER_SERVICE_H
#define CONTROLLER_SERVICE_H

// Interfacing module's class
namespace Controller {
	class Service {
	public:
		// Return the value that should be returned by main
		virtual int run(int argc, char* argv[]) = 0;

	};

	// Here you might have DTO structs and stuff to interface to us...
}

#endif // CONTROLLER_SERVICE_H
