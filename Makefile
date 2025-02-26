GAME      :=Star_Fox_64
GAME_LOWER:=star_fox_64
GAME_SHORT:=sf64

.PHONY: all
all: tools .WAIT n64patch pc

.PHONY: tools
tools:
	@$(MAKE) --no-print-directory -C tools

.PHONY: n64
n64:
	@$(MAKE) --no-print-directory -C n64

.PHONY: n64patch
n64patch:
	@$(MAKE) --no-print-directory -C n64 patch

.PHONY: pc
pc:
	@$(MAKE) --no-print-directory -C pc/EverDrive64

.PHONY: release
release: clean .WAIT all
	$(RM) -r\
		release/$(GAME_LOWER).apworld release/connector_$(GAME_SHORT)_bizhawk.lua release/connector_$(GAME_SHORT)_pj64.js\
		release/connector_$(GAME_SHORT)_ed64_linux release/connector_$(GAME_SHORT)_ed64.exe ap/__pycache__ ap/assets
	mkdir -p release ap/assets
	mv ap $(GAME_LOWER)
	ln n64/rom/$(GAME).patch $(GAME_LOWER)/assets/
	ln n64/rom/$(GAME)_Patched.z64-md5 $(GAME_LOWER)/assets/
	ln pc/Bizhawk.lua $(GAME_LOWER)/assets/connector_$(GAME_SHORT)_bizhawk.lua
	zip -qr9 release/$(GAME_LOWER).apworld $(GAME_LOWER)
	mv $(GAME_LOWER) ap
	cp pc/Bizhawk.lua release/connector_$(GAME_SHORT)_bizhawk.lua
	cp pc/Project64.js release/connector_$(GAME_SHORT)_pj64.js
	cp pc/EverDrive64/EverDrive64 release/connector_$(GAME_SHORT)_ed64_linux
	cp pc/EverDrive64/EverDrive64.exe release/connector_$(GAME_SHORT)_ed64.exe

clean:
	@$(MAKE) --no-print-directory -C tools clean
	@$(MAKE) --no-print-directory -C n64 clean
	@$(MAKE) --no-print-directory -C pc/EverDrive64 clean
