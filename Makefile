all:
	@echo "Compiling..."
	@ndk-build
	@echo "Building..."
	@ant debug
	@echo "done"

install:
	@echo "Compiling..."
	@ndk-build
	@echo "Building and installing..."
	@ant debug install
	@echo "done"

run:
	@echo "Launching"
	@adb shell monkey -p com.raisingthebar.projectr -c android.intent.category.LAUNCHER 1

debug:
	@echo "Compiling..."
	@ndk-build
	@echo "Building and installing..."
	@ant debug install
	@echo "Launching"
	@adb shell monkey -p com.raisingthebar.projectr -c android.intent.category.LAUNCHER 1
	@echo "Debugging:"
	@adb logcat | grep $$(adb shell ps | grep projectr | awk '{print $$2}')
	@echo "done"
