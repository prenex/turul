# Main-level make descriptor
# --------------------------
#
# List all implementation subdirectories with node.mk files in them
# The SimplePrinterServiceImpl is a header-only simple component so it doesn't need to be here.
SUBDIRS-y += SimpleAdderServiceImpl FilePrinterServiceImpl MainControllerServiceImpl #SimplePrinterServiceImpl 
# List all top-level *.o files - only the main.o should be here on this level for making things clean
OBJS-y    += main.o
# List all library (*.a) files here if necessary
LIBS-y    +=
