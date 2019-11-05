// -*- tab-width : 4 ; mode : Assembler -*-

# ブートセクタが設定する	
#define CYLS	0x0ff0
#define LEDS	0x0ff1
# 色数に関する情報。何ビットカラーか？	
#define VMODE	0x0ff2
# 解像度のX	
#define SCRNX	0x0ff4
# 解像度のY	
#define SCRNY	0x0ff6			
# グラフィックバッファの開始番地
#define VRAM	0x0ff8			
	
	.file "haribote.S"

	.code16
	
	.section .text	
	.global _start

	movb	$0x13, %al				# VGAグラフィックス、320x200x8bitカラー
	movb	$0x00, %ah
	int		$0x10

	movb	$8, (VMODE)				# 画面モードをメモする
	movw	$320, (SCRNX)
	movw	$200, (SCRNY)
	movl	$0x000a0000, (VRAM)

# キーボードのLED状態をBIOSに教えてもらう

	movb	$0x02, %ah
	int		$0x16 					# keyboard BIOS
	movb	%al, (LEDS)
	
fin:
	hlt
	jmp	fin
