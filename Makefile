GAME      :=Star_Fox_64
GAME_LOWER:=star_fox_64
GAME_SHORT:=sf64

.PHONY: all
all: tools n64 pc

.PHONY: tools
tools:
	@$(MAKE) --no-print-directory -C tools

.PHONY: n64
n64:
	@$(MAKE) --no-print-directory -C n64 patch

.PHONY: pc
pc:
	@$(MAKE) --no-print-directory -C pc/EverDrive64

.PHONY: release
release:
	$(RM) -r\
		release/$(GAME_LOWER).apworld release/connector_$(GAME_SHORT)_bizhawk.lua release/connector_$(GAME_SHORT)_pj64.js\
		release/connector_$(GAME_SHORT)_ed64_linux release/connector_$(GAME_SHORT)_ed64.exe ap/__pycache__
	mkdir -p release
	mv ap $(GAME_LOWER)
	ln n64/rom/$(GAME).patch $(GAME_LOWER)/
	zip -qr9 release/$(GAME_LOWER).apworld $(GAME_LOWER)
	rm $(GAME_LOWER)/$(GAME).patch
	mv $(GAME_LOWER) ap
	cp pc/Bizhawk.lua release/connector_$(GAME_SHORT)_bizhawk.lua
	cp pc/Project64.js release/connector_$(GAME_SHORT)_pj64.js
	cp pc/EverDrive64/EverDrive64 release/connector_$(GAME_SHORT)_ed64_linux
	cp pc/EverDrive64/EverDrive64.exe release/connector_$(GAME_SHORT)_ed64.exe

clean:
	@$(MAKE) --no-print-directory -C tools clean
	@$(MAKE) --no-print-directory -C n64 clean
	@$(MAKE) --no-print-directory -C pc/EverDrive64 clean
