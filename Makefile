all:
	@echo "Compiling..."
	@ndk-build
	@echo "Building..."
	@ant debug
	@echo "done"
install:
	@echo "Compiling..."
	@ndk-build
	@echo "Bulding and installing..."
	@ant debug install
	@echo "done"

