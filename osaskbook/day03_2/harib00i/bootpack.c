void HariMain(void)
{

  // おそらくこれの base address は 0x280000 にしないといけないので要修正
  
fin:
	/* ここにHLTを入れたいのだが、C言語ではHLTが使えない！ */
	goto fin;

}
