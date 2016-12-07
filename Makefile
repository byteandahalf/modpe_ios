DEVICE := ryans-ipod-touch.local
TESTSCRIPT := script.js
SCRIPTSDIR := /var/mobile/modpe/

PROJECT := modpe
DYLIB := $(PROJECT).dylib
PLIST := $(PROJECT).plist
DEB := $(PROJECT).deb

BUILD := build
STAGE := $(BUILD)/deb
SUBSTRATE := $(STAGE)/Library/MobileSubstrate/DynamicLibraries
SDK := /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk

SRCS := $(shell find . -type f -name '*.cpp')
OBJS := $(addprefix $(BUILD)/,$(SRCS:.cpp=.o))

ARCHS := -arch arm64
FRAMEWORKS := -framework CydiaSubstrate -framework Forklift
CXX := clang++ $(ARCHS)
LD := $(CXX) $(FRAMEWORKS)
override CXXFLAGS += -isysroot $(SDK) -stdlib=libc++ -std=c++11 -miphoneos-version-min=7.0
override LDFLAGS += $(CXXFLAGS)


### Build rules ###

all: $(DEB)

$(DYLIB): $(OBJS)
	@$(LD) $(LDFLAGS) -dynamiclib -o $@ $^

$(BUILD)/%.o: %.cpp
	@$(CXX) -c $(CXXFLAGS) $< -o $@

package: $(DEB)

$(DEB): $(DYLIB) $(PLIST)
	@echo '$(PROJECT): Staging debian package'
	-rm -rf $(STAGE)
	-mkdir -p $(STAGE)
	-cp -R layout/* $(BUILD)
	-mkdir -p $(SUBSTRATE)
	-cp $^ $(SUBSTRATE)
	-dpkg-deb -Zgzip -b $(STAGE) $@


### Deploy rules ###

install-ssh: $(DEB)
	@echo '$(PROJECT): Deploy via ssh'
	-scp $< root@$(DEVICE):/var/tmp/
	-ssh root@$(DEVICE)

deploy-ssh:
	@echo '$(PROJECT): Deploy script via ssh'
	-scp scripts/$(TESTSCRIPT) root@$(DEVICE):$(SCRIPTSDIR)

install-afc: $(DEB)
	@echo '$(PROJECT): Offline deploy via afc'
	-sudo afcclient put $< /$<
	-sudo afcclient put scripts/$(TESTSCRIPT) /$(TESTSCRIPT)


### Clean rules ###

clean:
	@echo '$(PROJECT): Clean build directory'
	-rm -rf $(BUILD)/*
	-mkdir -p $(STAGE)
	-cp -R layout/* $(BUILD)
	-rm $(DYLIB)
