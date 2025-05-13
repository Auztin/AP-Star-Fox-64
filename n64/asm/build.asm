.n64
.relativeinclude on

;version guard, prevent people from building with older armips versions
.if (version() < 110)
.notice version()
.error   "Detected armips build is too old. Please install https://github.com/Kingcom/armips version 0.11 or later."
.endif

.create patchedfile, 0
.incbin romfile

;replace game init with code that loads payload
.orga 0x59A8
.area 0x64, 0
.align 0x10
.importobj bootbundle
.endarea

.headersize (0x80400000 - 0xC00000)

.org    0x80400000
.area   0x00200000 ;payload max memory

AP_INPUT_PTR:
.word 0
AP_OUTPUT_PTR:
.word 0

;modify replaced code and add back to run later
init_game:
  JAL inject_hooks
  NOP
  .incbin romfile,0x59A8,0x64

PAYLOAD_START:

.align 0x10
.importobj srcbundle
.include "displaced.asm"
.include "assets.asm"

.align 0x10
AP_ASSETS:
.incbin assetsdir+"/assets.dl"

PAYLOAD_END:
.endarea ; payload max memory

.close
